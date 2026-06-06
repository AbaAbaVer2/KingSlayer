/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "onPlayCardClicked",
    "",
    "onRulesClicked",
    "onDrawPileClicked",
    "onDiscardPileClicked",
    "onRestartClicked",
    "onBossTookDamage",
    "damage",
    "animateCardsFlying",
    "QList<CardWidget*>",
    "widgets"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[11];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[18];
    char stringdata5[21];
    char stringdata6[17];
    char stringdata7[17];
    char stringdata8[7];
    char stringdata9[19];
    char stringdata10[19];
    char stringdata11[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 17),  // "onPlayCardClicked"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 14),  // "onRulesClicked"
        QT_MOC_LITERAL(45, 17),  // "onDrawPileClicked"
        QT_MOC_LITERAL(63, 20),  // "onDiscardPileClicked"
        QT_MOC_LITERAL(84, 16),  // "onRestartClicked"
        QT_MOC_LITERAL(101, 16),  // "onBossTookDamage"
        QT_MOC_LITERAL(118, 6),  // "damage"
        QT_MOC_LITERAL(125, 18),  // "animateCardsFlying"
        QT_MOC_LITERAL(144, 18),  // "QList<CardWidget*>"
        QT_MOC_LITERAL(163, 7)   // "widgets"
    },
    "MainWindow",
    "onPlayCardClicked",
    "",
    "onRulesClicked",
    "onDrawPileClicked",
    "onDiscardPileClicked",
    "onRestartClicked",
    "onBossTookDamage",
    "damage",
    "animateCardsFlying",
    "QList<CardWidget*>",
    "widgets"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    1,   61,    2, 0x08,    6 /* Private */,
       9,    1,   64,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onPlayCardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRulesClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDrawPileClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDiscardPileClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRestartClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBossTookDamage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'animateCardsFlying'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<CardWidget*> &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onPlayCardClicked(); break;
        case 1: _t->onRulesClicked(); break;
        case 2: _t->onDrawPileClicked(); break;
        case 3: _t->onDiscardPileClicked(); break;
        case 4: _t->onRestartClicked(); break;
        case 5: _t->onBossTookDamage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->animateCardsFlying((*reinterpret_cast< std::add_pointer_t<QList<CardWidget*>>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
