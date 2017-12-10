#!/bin/bash
DEVICE=$1
shift
echo $@ | dd of=$DEVICE bs=1
