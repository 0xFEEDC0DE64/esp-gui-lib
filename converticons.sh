#!/bin/bash

for i in icons/*
do
    build-iconconvert-Desktop_Qt_6_4_1-Debug/iconconvert $i src/icons/ icon_templ.h.tmpl icon_templ.cpp.tmpl
done
