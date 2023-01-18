#!/bin/bash

for i in icons/*
do
    build-iconconvert-Desktop_Qt_6_4_1-Debug/iconconvert $i src/icons/ icon_templ.h.tmpl icon_templ.cpp.tmpl

    ICON_NAME="$(basename "$i" .png)"
    case "$ICON_NAME" in
        icons_to_exclude)
            echo no grey version needed
            ;;
        *)
            build-iconconvert-Desktop_Qt_6_4_1-Debug/iconconvert "$i" src/icons/ icon_templ.h.tmpl icon_templ.cpp.tmpl --background-color "#5c5c5c" --name-override "${ICON_NAME}_grey"
            ;;
    esac
done
