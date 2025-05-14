// MyClicker.h
#pragma once

#include <QMap>
#include <QTimer>
#include <QWidget>
#include <Windows.h>
//utf-8
#pragma execution_character_set("utf-8")
namespace Ui
{
    class MyClickerClass;
}

class MyClicker : public QWidget
{
    Q_OBJECT

public:
    explicit MyClicker(QWidget* parent = nullptr);
    ~MyClicker() override;

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private slots:
    void OnStartStopClicked();

private:
    void InitKeyMappings();
    void InitHotKeys();
    void RegisterHotkey();
    void UnregisterHotkey();
    void SimulateAction();

private:
    Ui::MyClickerClass* ui;
    QTimer* m_timer;
    bool m_isRunning = false;
    int m_hotkeyId = 1;
    quint32 m_currentHotkey = VK_F8; // 默认热键

    QMap<QString, int> m_keyMap = {
        {"鼠标左键", VK_LBUTTON},
        {"鼠标右键", VK_RBUTTON},
        {"空格", VK_SPACE},
        {"上", VK_UP},
        {"下", VK_DOWN},
        {"左", VK_LEFT},
        {"右", VK_RIGHT},
        {"PGUP", VK_PRIOR},
        {"PGDN", VK_NEXT},
        {"HOME", VK_HOME},
        {"END", VK_END},
        {"INSERT", VK_INSERT},
        {"DELETE", VK_DELETE},
        {"回车", VK_RETURN},
        {"ESC", VK_ESCAPE},
        {"TAB", VK_TAB},
        {"CTRL", VK_CONTROL},
        {"ALT", VK_MENU},
        {"SHIFT", VK_SHIFT},
        {"A", 0x41}, // A
        {"B", 0x42}, // B
        {"C", 0x43}, // C
        {"D", 0x44}, // D
        {"E", 0x45}, // E
        {"F", 0x46}, // F
        {"G", 0x47}, // G
        {"H", 0x48}, // H
        {"I", 0x49}, // I
        {"J", 0x4A}, // J
        {"K", 0x4B}, // K
        {"L", 0x4C}, // L
        {"M", 0x4D}, // M
        {"N", 0x4E}, // N
        {"O", 0x4F}, // O
        {"P", 0x50}, // P
        {"Q", 0x51}, // Q
        {"R", 0x52}, // R
        {"S", 0x53}, // S
        {"T", 0x54}, // T
        {"U", 0x55}, // U
        {"V", 0x56}, // V
        {"W", 0x57}, // W
        {"X", 0x58}, // X
        {"Y", 0x59}, // Y
        {"Z", 0x5A} // Z
    };

    QMap<QString, quint32> m_hotkeyMap = {
        {"F1", VK_F1},
        {"F2", VK_F2},
        {"F3", VK_F3},
        {"F4", VK_F4},
        {"F5", VK_F5},
        {"F6", VK_F6},
        {"F7", VK_F7},
        {"F8", VK_F8},
        {"F9", VK_F9},
        {"F10", VK_F10},
        {"F11", VK_F11},
        {"F12", VK_F12},
    };
};
