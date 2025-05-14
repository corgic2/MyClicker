// MyClicker.cpp
#include "MyClicker.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_MyClicker.h"

MyClicker::MyClicker(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MyClickerClass)
    , m_timer(new QTimer(this))
{
    ui->setupUi(this);

    // 初始化映射
    InitKeyMappings();
    InitHotKeys();

    // 设置定时器
    connect(m_timer, &QTimer::timeout, this, &MyClicker::SimulateAction);
    connect(ui->comboBox_HotKey, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index)
            {
                Q_UNUSED(index)
                if (!m_isRunning)
                {
                    // 仅在非运行状态允许修改热键
                    RegisterHotkey();
                }
            });
    // 初始热键注册
    RegisterHotkey();
}

MyClicker::~MyClicker()
{
    UnregisterHotkey();
    delete ui;
}

void MyClicker::InitKeyMappings()
{
    // 初始化动作选择
    ui->comboBox_Key->clear();
    foreach(auto key, m_keyMap.keys())
    {
        ui->comboBox_Key->addItem(key);
    }
}

void MyClicker::InitHotKeys()
{
    // 初始化热键选择
    ui->comboBox_HotKey->clear();
    foreach(auto key, m_hotkeyMap.keys())
    {
        ui->comboBox_HotKey->addItem(key);
    }
    ui->comboBox_HotKey->setCurrentText("F8");
}

bool MyClicker::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    auto msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY && msg->wParam == m_hotkeyId)
    {
        OnStartStopClicked();
        return true;
    }
    return QWidget::nativeEvent(eventType, message, result);
}

void MyClicker::OnStartStopClicked()
{
    m_isRunning = !m_isRunning;

    if (m_isRunning)
    {
        bool ok;
        int interval = ui->lineEdit_Time->text().toInt(&ok);

        if (!ok || interval <= 0)
        {
            QMessageBox::warning(this, "错误", "间隔时间必须为正整数");
            m_isRunning = false;
            return;
        }

        m_timer->start(interval);
        ui->comboBox_HotKey->setEnabled(false);
        ui->comboBox_Key->setEnabled(false);
        ui->lineEdit_Time->setEnabled(false);
    }
    else
    {
        m_timer->stop();
        ui->comboBox_HotKey->setEnabled(true);
        ui->comboBox_Key->setEnabled(true);
        ui->lineEdit_Time->setEnabled(true);
    }
}

void MyClicker::SimulateAction()
{
    INPUT input[2] = {0};
    QString currentAction = ui->comboBox_Key->currentText();
    int keyCode = m_keyMap.value(currentAction, VK_LBUTTON);

    // 处理鼠标事件
    if (currentAction.contains("鼠标"))
    {
        input[0].type = INPUT_MOUSE;
        input[1].type = INPUT_MOUSE;

        if (currentAction == "鼠标左键")
        {
            input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        }
        else
        {
            input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        }
    }
    // 处理键盘事件
    else
    {
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = keyCode;
        input[1].type = INPUT_KEYBOARD;
        input[1].ki.wVk = keyCode;
        input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    }

    SendInput(2, input, sizeof(INPUT));
}

void MyClicker::RegisterHotkey()
{
    UnregisterHotkey();

    QString hotkey = ui->comboBox_HotKey->currentText();
    m_currentHotkey = m_hotkeyMap.value(hotkey, VK_F8);

    if (!RegisterHotKey(reinterpret_cast<HWND>(winId()),
                        m_hotkeyId,
                        MOD_NOREPEAT,
                        m_currentHotkey))
    {
        QMessageBox::warning(this, "警告", "热键注册失败，可能已被占用");
    }
}

void MyClicker::UnregisterHotkey()
{
    UnregisterHotKey(reinterpret_cast<HWND>(winId()), m_hotkeyId);
}
