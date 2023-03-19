#include "ClickableHBoxLayout.hpp"
#include <qboxlayout.h>

using namespace babel;

ClickableHBoxLayout::ClickableHBoxLayout(QWidget *parent) : QHBoxLayout(parent) {
}

void ClickableHBoxLayout::mousePressEvent(QMouseEvent *event) {
    printf("clicked!\n");
    emit this->clicked();
}

#include <memory>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClickableHBoxLayout.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_babel__ClickableHBoxLayout_t {
    QByteArrayData data[3];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_babel__ClickableHBoxLayout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_babel__ClickableHBoxLayout_t qt_meta_stringdata_babel__ClickableHBoxLayout = {
    {
QT_MOC_LITERAL(0, 0, 26), // "babel::ClickableHBoxLayout"
QT_MOC_LITERAL(1, 27, 7), // "clicked"
QT_MOC_LITERAL(2, 35, 0) // ""

    },
    "babel::ClickableHBoxLayout\0clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_babel__ClickableHBoxLayout[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void babel::ClickableHBoxLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClickableHBoxLayout *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClickableHBoxLayout::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClickableHBoxLayout::clicked)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject babel::ClickableHBoxLayout::staticMetaObject = { {
    QMetaObject::SuperData::link<QHBoxLayout::staticMetaObject>(),
    qt_meta_stringdata_babel__ClickableHBoxLayout.data,
    qt_meta_data_babel__ClickableHBoxLayout,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *babel::ClickableHBoxLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *babel::ClickableHBoxLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_babel__ClickableHBoxLayout.stringdata0))
        return static_cast<void*>(this);
    return QHBoxLayout::qt_metacast(_clname);
}

int babel::ClickableHBoxLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void babel::ClickableHBoxLayout::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

