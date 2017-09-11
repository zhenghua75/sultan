TEMPLATE  = subdirs
CONFIG   += ordered

!contains(CONFIG, SINGLEBIN) {
    SUBDIRS = \
        libglobal \
        libdb \
        libserver \
        libprint \
        libgui \
        libguiqml
}

SUBDIRS += sultan
