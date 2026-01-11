
#include <QtCore>

extern void setup(QString serverName);
extern void loop();

extern "C"
{

Q_DECL_EXPORT
void FluidNC(QString serverName)
{
    setup(serverName);
    while (1) {
        loop();
    }
}

}
