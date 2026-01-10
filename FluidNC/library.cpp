
#include <QtCore>

extern void setup(QString serverName);
extern void loop();

Q_DECL_EXPORT
void FluidNC(QString serverName)
{
    setup(serverName);
    while (1) {
        loop();
    }
}
