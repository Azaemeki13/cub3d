#!/usr/bin/env bash
set -Eeuo pipefail

MAP=${1:-./maps/scary.cub}
BIN=./cub3D
SUPP=./valgrind_x11.supp
LOG="valgrind-$(date +%F_%H%M%S).log"

command -v valgrind >/dev/null || { echo "valgrind not found in PATH"; exit 1; }

make

# Ensure the binary exists; if not, try a full rebuild
[ -x "$BIN" ] || make re
[ -x "$BIN" ] || { echo "Build didn't produce $BIN"; exit 1; }

[ -f "$MAP" ] || { echo "Map file '$MAP' not found."; exit 1; }

VG_ARGS=(
  --leak-check=full
  --show-leak-kinds=all
  --track-origins=yes
  --log-file="$LOG"
)

[ -f "$SUPP" ] && VG_ARGS+=(--suppressions="$SUPP")

echo "Running: valgrind ${VG_ARGS[*]} $BIN $MAP"
valgrind "${VG_ARGS[@]}" "$BIN" "$MAP"

# Now clean object files (keeps binary in standard 42 Makefiles; adjust if yours differs)
make clean || true

echo "Done. Log written to: $LOG"
