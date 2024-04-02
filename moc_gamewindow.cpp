/****************************************************************************
** Meta object code from reading C++ file 'gamewindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gamewindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGameWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGameWindowENDCLASS = QtMocHelpers::stringData(
    "GameWindow",
    "betPlaced",
    "",
    "onContinueClicked",
    "onHorseSelected",
    "onBetEntered",
    "updateMoneyPool",
    "newAmount",
    "checkBetResult",
    "winningHorseIndex",
    "odds",
    "resetWindow",
    "displayBettingHistory"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGameWindowENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[11];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[16];
    char stringdata5[13];
    char stringdata6[16];
    char stringdata7[10];
    char stringdata8[15];
    char stringdata9[18];
    char stringdata10[5];
    char stringdata11[12];
    char stringdata12[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGameWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGameWindowENDCLASS_t qt_meta_stringdata_CLASSGameWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "GameWindow"
        QT_MOC_LITERAL(11, 9),  // "betPlaced"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 17),  // "onContinueClicked"
        QT_MOC_LITERAL(40, 15),  // "onHorseSelected"
        QT_MOC_LITERAL(56, 12),  // "onBetEntered"
        QT_MOC_LITERAL(69, 15),  // "updateMoneyPool"
        QT_MOC_LITERAL(85, 9),  // "newAmount"
        QT_MOC_LITERAL(95, 14),  // "checkBetResult"
        QT_MOC_LITERAL(110, 17),  // "winningHorseIndex"
        QT_MOC_LITERAL(128, 4),  // "odds"
        QT_MOC_LITERAL(133, 11),  // "resetWindow"
        QT_MOC_LITERAL(145, 21)   // "displayBettingHistory"
    },
    "GameWindow",
    "betPlaced",
    "",
    "onContinueClicked",
    "onHorseSelected",
    "onBetEntered",
    "updateMoneyPool",
    "newAmount",
    "checkBetResult",
    "winningHorseIndex",
    "odds",
    "resetWindow",
    "displayBettingHistory"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGameWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    0,   64,    2, 0x08,    3 /* Private */,
       5,    0,   65,    2, 0x08,    4 /* Private */,
       6,    1,   66,    2, 0x08,    5 /* Private */,
       8,    2,   69,    2, 0x0a,    7 /* Public */,
      11,    0,   74,    2, 0x0a,   10 /* Public */,
      12,    0,   75,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSGameWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGameWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGameWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameWindow, std::true_type>,
        // method 'betPlaced'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onContinueClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHorseSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBetEntered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateMoneyPool'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'checkBetResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'resetWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayBettingHistory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->betPlaced(); break;
        case 1: _t->onContinueClicked(); break;
        case 2: _t->onHorseSelected(); break;
        case 3: _t->onBetEntered(); break;
        case 4: _t->updateMoneyPool((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 5: _t->checkBetResult((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->resetWindow(); break;
        case 7: _t->displayBettingHistory(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameWindow::*)();
            if (_t _q_method = &GameWindow::betPlaced; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *GameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGameWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GameWindow::betPlaced()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
