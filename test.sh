#!/bin/bash

rm -rf shared/*

unalias cp || true && \
cp -f ./* shared/

# C-a x to forcefully exit from qemu serial
docker compose run --rm buildenv && \
docker compose run --rm qemu
