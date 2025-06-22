#!/bin/bash

# Parcourir tous les dossiers dans le répertoire actuel
for dir in */; do
  if [ -d "$dir" ]; then
    echo "Entrée dans le dossier: $dir"
    (cd "$dir" && make clean)
  fi
done
