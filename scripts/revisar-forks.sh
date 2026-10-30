#!/usr/bin/env bash
# 1. revisa todos los forks del repositorio y abre un pull request por cada fork
#    que tenga commits nuevos en main y que no tenga ya un pull request abierto.
#    el pull request se asigna al docente, le pide revision y lo menciona,
#    e indica si el estudiante modifico archivos fuera de su carpeta.
#    un pull request abierto se actualiza solo con los commits nuevos del fork.
# 2. revisa los pull requests abiertos y, si alguno tiene conflictos,
#    comenta mencionando al estudiante con instrucciones para resolverlo
#    (una sola vez por cada commit nuevo del estudiante).
#
# uso (desde la raiz del repositorio):
#   ./scripts/revisar-forks.sh             # abre pull requests y comenta conflictos
#   ./scripts/revisar-forks.sh --simulacro # solo muestra lo que haria
#
# variables:
#   DOCENTE  usuario de github a quien asignar (por defecto, el usuario de gh)
#
# requiere: gh (autenticado) y jq

set -euo pipefail

simulacro=false
[[ "${1:-}" == "--simulacro" ]] && simulacro=true

repositorio=$(gh repo view --json nameWithOwner --jq .nameWithOwner)
dueno=${repositorio%%/*}
rama_base=$(gh repo view --json defaultBranchRef --jq .defaultBranchRef.name)
docente=${DOCENTE:-$(gh api user --jq .login)}
raiz=$(git rev-parse --show-toplevel)

# carpetas compartidas donde los estudiantes tambien pueden trabajar
carpetas_compartidas="00-proyecto-2"

abiertos=()
comentados=()
con_errores=()

# mensaje para el estudiante cuando su pull request tiene conflictos
mensaje_conflicto() {
  local usuario=$1 rama=$2
  cat <<EOF
@$usuario hola! tus cambios recientes no se pudieron fusionar con el repositorio principal, porque chocan con cambios que hicieron otras personas (hay un conflicto).

para resolverlo:

1. guarda una copia de tus archivos nuevos o modificados en algun lugar de tu computador, fuera de la carpeta del repositorio.
2. entra a tu fork en https://github.com/$usuario/${repositorio#*/}, presiona **Sync fork** y luego **Discard commits**, para que tu fork quede igual al repositorio principal.
3. en tu computador, borra la carpeta local del repositorio y vuelve a clonar tu fork.
4. copia tus archivos de vuelta a tu carpeta, y haz commit y push de nuevo.

este pull request se actualizara solo cuando hagas push.

<!-- conflicto -->
EOF
}

# busca la carpeta NN-usuario que corresponde al estudiante (sin distinguir mayusculas)
carpeta_de() {
  local usuario_min
  usuario_min=$(echo "$1" | tr '[:upper:]' '[:lower:]')
  for carpeta in "$raiz"/[0-9][0-9]-*/; do
    local nombre=${carpeta%/}
    nombre=${nombre##*/}
    local sufijo
    sufijo=$(echo "${nombre#*-}" | tr '[:upper:]' '[:lower:]')
    if [[ "$sufijo" == "$usuario_min" ]]; then
      echo "$nombre"
      return
    fi
  done
}

# espera a que github calcule si el pull request se puede fusionar
estado_fusion() {
  local numero=$1 estado
  for _ in $(seq 1 10); do
    estado=$(gh pr view "$numero" --repo "$repositorio" --json mergeable --jq .mergeable)
    [[ "$estado" != "UNKNOWN" ]] && { echo "$estado"; return; }
    sleep 3
  done
  echo "UNKNOWN"
}

# paso 1: abrir pull requests nuevos

prs_abiertos=$(gh pr list --repo "$repositorio" --state open --limit 200 \
  --json headRepositoryOwner,headRefName)

forks=$(gh api "repos/$repositorio/forks" --paginate \
  --jq '.[] | "\(.owner.login) \(.default_branch)"')

while read -r usuario rama; do
  [[ "$usuario" == "$docente" ]] && continue

  ya_existe=$(echo "$prs_abiertos" | jq -r --arg u "$usuario" --arg r "$rama" \
    '[.[] | select(.headRepositoryOwner.login == $u and .headRefName == $r)] | length')
  [[ "$ya_existe" != "0" ]] && continue

  if ! comparacion=$(gh api "repos/$repositorio/compare/$rama_base...$usuario:$rama" 2>/dev/null); then
    con_errores+=("$usuario: no se pudo comparar el fork")
    continue
  fi

  adelante=$(echo "$comparacion" | jq .ahead_by)
  [[ "$adelante" == "0" ]] && continue

  carpeta=$(carpeta_de "$usuario")
  permitidas="${carpeta:-__sin_carpeta__} $carpetas_compartidas"
  patron="^($(echo "$permitidas" | tr ' ' '|'))/"
  fuera=$(echo "$comparacion" | jq -r '.files[]? | .filename, (.previous_filename // empty)' \
    | grep -Ev "$patron" || true)

  if [[ -z "$carpeta" ]]; then
    revision="⚠️ no existe una carpeta NN-$usuario/ en el repositorio"
  elif [[ -n "$fuera" ]]; then
    revision="⚠️ modifica archivos fuera de \`$carpeta/\`:"$'\n'"$(echo "$fuera" | head -n10 | sed 's/^/- `/; s/$/`/')"
  else
    revision="✅ solo modifica \`$carpeta/\` y carpetas compartidas"
  fi

  echo "== $usuario: $adelante commit(s) nuevo(s)"
  if $simulacro; then
    echo "   (simulacro) abriria pull request: $revision"
    continue
  fi

  cuerpo="@$docente pull request automatico desde \`$usuario:$rama\` ($adelante commit(s))."$'\n\n'"$revision"
  if url=$(gh pr create --repo "$repositorio" --base "$rama_base" --head "$usuario:$rama" \
    --title "cambios de $usuario" --body "$cuerpo" \
    --assignee "$docente" --reviewer "$docente" --no-maintainer-edit); then
    echo "   $url"
    abiertos+=("$url")
  else
    con_errores+=("$usuario: no se pudo abrir el pull request")
  fi
done <<< "$forks"

# paso 2: avisar a estudiantes con conflictos

prs=$(gh pr list --repo "$repositorio" --state open --limit 200 \
  --json number,headRepositoryOwner,headRefName,headRefOid \
  --jq ".[] | select(.headRepositoryOwner.login != \"$dueno\") | \"\(.number) \(.headRepositoryOwner.login) \(.headRefName) \(.headRefOid)\"")

while read -r numero usuario rama commit; do
  [[ -z "$numero" ]] && continue
  [[ "$(estado_fusion "$numero")" != "CONFLICTING" ]] && continue

  marca="<!-- conflicto:$commit -->"
  if gh pr view "$numero" --repo "$repositorio" --json comments --jq '.comments[].body' \
    | grep -qF "$marca"; then
    continue
  fi

  echo "== #$numero $usuario: tiene conflictos"
  if $simulacro; then
    echo "   (simulacro) comentaria avisando a @$usuario"
    continue
  fi

  mensaje=$(mensaje_conflicto "$usuario" "$rama")
  if gh pr comment "$numero" --repo "$repositorio" --body "${mensaje/<!-- conflicto -->/$marca}" >/dev/null; then
    comentados+=("#$numero $usuario")
  else
    con_errores+=("#$numero $usuario: no se pudo comentar")
  fi
done <<< "$prs"

echo
echo "pull requests abiertos (${#abiertos[@]}):"
printf '  %s\n' "${abiertos[@]+"${abiertos[@]}"}"
echo "avisos de conflicto (${#comentados[@]}):"
printf '  %s\n' "${comentados[@]+"${comentados[@]}"}"
echo "errores (${#con_errores[@]}):"
printf '  %s\n' "${con_errores[@]+"${con_errores[@]}"}"

# si hubo errores, la ejecucion queda marcada como fallida en github actions
[[ ${#con_errores[@]} -eq 0 ]]
