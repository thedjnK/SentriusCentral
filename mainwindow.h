/************************************************************************
* thedjnK's Sentrius Programmer                                         *
* Copyright (C) 2018, thedjnK                                           *
*                                                                       *
* File: mainwindow.h                                                    *
* Version: 0.01a                                                        *
* Last Updated: 14/11/2018                                              *
*                                                                       *
* Parts of code used in this application come from Laird's UwTerminalX, *
* licensed under the GPLv3 from https://github.com/LairdCP/UwTerminalX  *
*                                                                       *
* License terms are as follows:                                         *
*                                                                       *
* This program is free software: you can redistribute it and/or         *
* modify it under the terms of the GNU General Public License as        *
* published by the Free Software Foundation, version 3.                 *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program.  If not, see http://www.gnu.org/licenses/    *
*                                                                       *
************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Includes
#include <QMainWindow>
#include <QMessageBox>
#include <QStatusBar>
#include <QtSerialPort/QtSerialPort>
#include <QFileDialog>
#include <QDebug>

//
const QColor BACKGROUND_COLOUR_NOT_SEEN = Qt::red;
const QColor BACKGROUND_COLOUR_PROGRAMMED = Qt::green;
const QColor BACKGROUND_COLOUR_IN_PROGRESS = Qt::yellow;
const QByteArray LINE_END_CHARACTER = "\r";
const qint32 CONNECT_RESPONSE_TIMEOUT = 500;

//Commands
#define COMMAND_MESSAGE_END                    0x0d //Character which separates commands (0x0d = carriage return)
#define COMMAND_MESSAGE_DELIMITER              " "  //Used to separate message components in incoming messages
#define COMMAND_MESSAGE_RESET                  "RE"
#define COMMAND_MESSAGE_SCAN                   "SC"
#define COMMAND_MESSAGE_CONNECT                "CN"
#define COMMAND_MESSAGE_DISCONNECT             "DC"
#define COMMAND_MESSAGE_SET                    "GO" //Send values to program to module
#define COMMAND_MESSAGE_VERSION                "VE" //send app version
#define COMMAND_MESSAGE_IDLE                   "ID" //disconnect and stop scanning
#define COMMAND_MESSAGE_NOOP                   "NO"
#define COMMAND_MESSAGE_MODE                   "MO" //sends back device mode: scanning, idle, connected, updating, etc.
#define COMMAND_MESSAGE_QUERY                  "QU" //sends back details of connected device
#define COMMAND_MESSAGE_UPTIME                 "UP" //sends back uptime of BL654
//#define COMMAND_MESSAGE_

//Response messages
#define RESPONSE_MESSAGE_DELIMITER             " "  //Used to separate message components in outgoing messages
#define RESPONSE_MESSAGE_END                   '\r' //End of each response message
#define RESPONSE_MESSAGE_ON_ERROR              "E1"
#define RESPONSE_MESSAGE_GATT_READ_ERROR       "E2"
#define RESPONSE_MESSAGE_GATT_WRITE_ERROR      "E3"
#define RESPONSE_MESSAGE_CHAR_MISSING_ERROR    "E4"
#define RESPONSE_MESSAGE_STATE_MACHINE_ERROR   "E5"
#define RESPONSE_MESSAGE_SCAN_ERROR            "E6"
#define RESPONSE_MESSAGE_CONNECT_ERROR         "E7"
#define RESPONSE_MESSAGE_CONNECTED_ERROR       "E9"
#define RESPONSE_MESSAGE_ADVERT                "AD"
#define RESPONSE_MESSAGE_CONNECT               "CN"
#define RESPONSE_MESSAGE_DISCONNECT            "DC"
#define RESPONSE_MESSAGE_CONNECTION_TIMEOUT    "CT"
#define RESPONSE_MESSAGE_READY                 "RD"
#define RESPONSE_MESSAGE_NOOP                  "NO"
#define RESPONSE_MESSAGE_UPTIME                "UP"
#define RESPONSE_MESSAGE_ACKNOWLEDGE           "AC"
#define RESPONSE_MESSAGE_STARTUP               "ST"
#define RESPONSE_MESSAGE_VERSION               "VE"

const QString APP_VERSION = "v0.01a";

const uint8_t MESSAGE_ID_LENGTH                             = 2;
const uint8_t RESPONSE_MESSAGE_ADVERT_INDEX_BLE_ADDRESS     = 3;
const uint8_t RESPONSE_MESSAGE_ADVERT_INDEX_RSSI            = 18;
const uint8_t RESPONSE_MESSAGE_ADVERT_INDEX_DEV_EUI         = 22;
const uint8_t RESPONSE_MESSAGE_ADVERT_LENGTH_BLE_ADDRESS    = 14;
const uint8_t RESPONSE_MESSAGE_ADVERT_LENGTH_RSSI           = 3;
const uint8_t RESPONSE_MESSAGE_ADVERT_LENGTH_DEV_EUI        = 16;
const uint8_t RESPONSE_MESSAGE_ADVERT_LENGTH                = 38;

const uint8_t RESPONSE_MESSAGE_VERSION_INDEX_VERSION        = 3;
const uint8_t RESPONSE_MESSAGE_VERSION_LENGTH_VERSION       = 4;
const uint8_t RESPONSE_MESSAGE_VERSION_LENGTH               = 7;

const uint8_t SCAN_TABLE_COLUMN_DEV_EUI = 0;
const uint8_t SCAN_TABLE_COLUMN_BLE_ADDRESS = 1;
const uint8_t SCAN_TABLE_COLUMN_RSSI = 2;

//Debug output style
#define DEBUG_OUT qDebug().nospace().noquote()

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //State machine process
    enum State {Idle, Resetting, Version, Scanning, ScanningUpdate, Connecting, Connected, Updating};
    Q_ENUM(State)
//TODO: ^ need to differentiate between scanning for devices for listing details and scanning for devices to update them

private slots:
    void on_btn_Connect_clicked();
    void on_btn_Scan_clicked();
    void on_btn_ScanClear_clicked();
    void on_btn_ScanExport_clicked();
    void on_btn_ConfigurationButton_clicked();
    void on_btn_Refresh_clicked();
    void on_combo_Port_currentIndexChanged(int);
    void SerialRead();
    void SerialError(QSerialPort::SerialPortError speErrorCode);
    void SerialBytesWritten(qint64 intByteCount);
    void SerialPortClosing();
    void on_btn_Programming_Start_clicked();
    void on_btn_Programming_Stop_clicked();

private:
    //Variables
    Ui::MainWindow *ui;         //GUI
    QSerialPort gspSerialPort;  //Serial port handle
    State CState;               //Current state
    QByteArray baRecBuffer;     //Receive buffer

    //Functions
    void ProcessData();
    QString PluralText(int i);
};

#endif // MAINWINDOW_H
