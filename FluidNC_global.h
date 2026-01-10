#ifndef FLUIDNC_GLOBAL_H
#define FLUIDNC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FLUIDNC_LIBRARY)
#    define FLUIDNC_EXPORT Q_DECL_EXPORT
#else
#    define FLUIDNC_EXPORT Q_DECL_IMPORT
#endif

#endif  // FLUIDNC_GLOBAL_H
