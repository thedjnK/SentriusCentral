/************************************************************************
* thedjnK's Sentrius Programmer                                         *
* Copyright (C) 2018, thedjnK                                           *
*                                                                       *
* File: mainwindow.cpp                                                  *
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

//Includes
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Window constructor
    ui->setupUi(this);
//ui->list_Programmed->item(0)->setBackgroundColor(BACKGROUND_COLOUR_NOT_SEEN);
//ui->list_Programmed->item(1)->setBackgroundColor(BACKGROUND_COLOUR_PROGRAMMED);
//ui->list_Programmed->item(2)->setBackgroundColor(BACKGROUND_COLOUR_IN_PROGRESS);

    //Gather list of serial port devices
    on_btn_Refresh_clicked();

    //Idle state
    CState = Idle;

    //Show version in status bar
    ui->statusBar->showMessage(QString("thedjnK's Sentrius Programmer, ").append(APP_VERSION));

    //
//    ui->table_ScanResults->verticalHeader()->setSectionsMovable(true);

    QPixmap abc("/tmp/BL654SC.png");
    ui->frame->setFixedHeight(abc.size().height());
    ui->frame->setFixedWidth(abc.size().width());
    ui->frame->setStyleSheet("background-image: url(/tmp/BL654SC.png); background-repeat:no-repeat;");
    //ui->frame->setStyleSheet("border-image: url(/tmp/BL654SC.png) 0 0 0 0 stretch stretch;");

/*    ui->table_ProgramResults->item(0, 0)->setBackgroundColor(BACKGROUND_COLOUR_IN_PROGRESS);
    ui->table_ProgramResults->item(0, 1)->setBackgroundColor(BACKGROUND_COLOUR_IN_PROGRESS);
    ui->table_ProgramResults->item(1, 0)->setBackgroundColor(BACKGROUND_COLOUR_PROGRAMMED);
    ui->table_ProgramResults->item(1, 1)->setBackgroundColor(BACKGROUND_COLOUR_PROGRAMMED);
    ui->table_ProgramResults->item(2, 0)->setBackgroundColor(BACKGROUND_COLOUR_NOT_SEEN);
    ui->table_ProgramResults->item(2, 1)->setBackgroundColor(BACKGROUND_COLOUR_NOT_SEEN);*/
}

MainWindow::~MainWindow()
{
    //Window destructor
    delete ui;
}

void MainWindow::on_btn_Connect_clicked()
{
    //Function to open serial port
    if (gspSerialPort.isOpen() == true)
    {
        //Serial port is already open - cancel any pending operations
//        if (gbTermBusy == true)
//        {
//            //Run cancel operation
//            on_btn_Cancel_clicked();
//        }

        //Close serial port
        while (gspSerialPort.isOpen() == true)
        {
            gspSerialPort.clear();
            gspSerialPort.close();
        }
//        gpSignalTimer->stop();

        //Change status message
        ui->statusBar->showMessage("");

        //Close log file if open
//        if (gpMainLog->IsLogOpen() == true)
//        {
//            gpMainLog->CloseLogFile();
//        }
    }

    if (ui->combo_Port->currentText().length() > 0)
    {
        //Port selected: setup serial port
        gspSerialPort.setPortName(ui->combo_Port->currentText());
        gspSerialPort.setBaudRate(ui->combo_Baud->currentText().toInt());
        gspSerialPort.setDataBits(QSerialPort::Data8);
        gspSerialPort.setStopBits(QSerialPort::OneStop);
        gspSerialPort.setParity(QSerialPort::NoParity);

        //Flow control
        gspSerialPort.setFlowControl((ui->combo_Flow->currentIndex() == 0 ? QSerialPort::HardwareControl : QSerialPort::NoFlowControl));

        if (gspSerialPort.open(QIODevice::ReadWrite))
        {
            //Successful
//            ui->statusBar->showMessage(QString("[").append(ui->combo_Port->currentText()).append(":").append(ui->combo_Baud->currentText()).append(",").append((ui->combo_Parity->currentIndex() == 0 ? "N" : ui->combo_Parity->currentIndex() == 1 ? "O" : ui->combo_Parity->currentIndex() == 2 ? "E" : "")).append(",").append(ui->combo_Data->currentText()).append(",").append(ui->combo_Stop->currentText()).append(",").append((ui->combo_Handshake->currentIndex() == 0 ? "N" : ui->combo_Handshake->currentIndex() == 1 ? "H" : ui->combo_Handshake->currentIndex() == 2 ? "S" : "")).append("]{").append((ui->radio_LCR->isChecked() ? "cr" : (ui->radio_LLF->isChecked() ? "lf" : (ui->radio_LCRLF->isChecked() ? "cr lf" : (ui->radio_LLFCR->isChecked() ? "lf cr" : ""))))).append("}"));

            //Update tooltip of system tray
//            if (gbSysTrayEnabled == true)
//            {
//                gpSysTray->setToolTip(QString("UwTerminalX v").append(UwVersion).append(" (").append(ui->combo_Port->currentText()).append(")"));
//            }

            //Switch to Terminal tab if not on terminal or speed testing tab
//            if (ui->selector_Tab->currentIndex() != ui->selector_Tab->indexOf(ui->tab_Term) && ui->selector_Tab->currentIndex() != ui->selector_Tab->indexOf(ui->tab_SpeedTest))
//            {
//                ui->selector_Tab->setCurrentIndex(ui->selector_Tab->indexOf(ui->tab_Term));
//            }

            //Break
//            gspSerialPort.setBreakEnabled(ui->check_Break->isChecked());

            //Update button text
//            ui->btn_TermClose->setText("C&lose Port");

            //Signal checking
//            SerialStatus(1);

            //Enable timer
//            gpSignalTimer->start(gpTermSettings->value("SerialSignalCheckInterval", DefaultSerialSignalCheckInterval).toUInt());

            //Disable log options
//            ui->edit_LogFile->setEnabled(false);
//            ui->check_LogEnable->setEnabled(false);
//            ui->check_LogAppend->setEnabled(false);
//            ui->btn_LogFileSelect->setEnabled(false);

            //Clear last received date/time
//            ui->label_LastRx->setText("N/A");

            //Open log file
#ifdef LOGGING
            if (ui->check_LogEnable->isChecked() == true)
            {
                //Logging is enabled
#ifdef TARGET_OS_MAC
                if (gpMainLog->OpenLogFile(QString((ui->edit_LogFile->text().left(1) == "/" || ui->edit_LogFile->text().left(1) == "\\") ? "" : QStandardPaths::writableLocation(QStandardPaths::DataLocation)).append("/").append(ui->edit_LogFile->text())) == LOG_OK)
#else
                if (gpMainLog->OpenLogFile(ui->edit_LogFile->text()) == LOG_OK)
#endif
                {
                    //Log opened
                    if (ui->check_LogAppend->isChecked() == false)
                    {
                        //Clear the log file
                        gpMainLog->ClearLog();
                    }
                    gpMainLog->WriteLogData(tr("-").repeated(31));
                    gpMainLog->WriteLogData(tr("\n Log opened ").append(QDate::currentDate().toString("dd/MM/yyyy")).append(" @ ").append(QTime::currentTime().toString("hh:mm")).append(" \n"));
                    gpMainLog->WriteLogData(tr(" UwTerminalX ").append(UwVersion).append(" \n"));
                    gpMainLog->WriteLogData(QString(" Port: ").append(ui->combo_Port->currentText()).append("\n"));
                    gpMainLog->WriteLogData(tr("-").repeated(31).append("\n\n"));
                    gbMainLogEnabled = true;
                }
                else
                {
                    //Log not writeable
                    QString strMessage = tr("Error whilst opening log.\nPlease ensure you have access to the log file ").append(ui->edit_LogFile->text()).append(" and have enough free space on your hard drive.");
                    gpmErrorForm->show();
                    gpmErrorForm->SetMessage(&strMessage);
                }
            }
#endif

            //Check which mode the device is in
            gspSerialPort.write(COMMAND_MESSAGE_NOOP);
            gspSerialPort.write(LINE_END_CHARACTER);
            gspSerialPort.waitForReadyRead(CONNECT_RESPONSE_TIMEOUT);

            if (!gspSerialPort.bytesAvailable())
            {
                //Nothing received
                gspSerialPort.close();
                QMessageBox::critical(this, "Unknown module or state", "Your module is not responding to commands, ensure you have chosen the correct options and try again.", QMessageBox::Close, QMessageBox::Close);
            }
            else
            {
                //Check which mode module is in
                QByteArray baTmpBuffer = gspSerialPort.readAll();
//                qDebug() << "Got: " << baTmpBuffer;
                if (baTmpBuffer.indexOf("\n01\tE007\r") >= 0)
                {
                    //Interactive mode
                    gspSerialPort.close();
                    QMessageBox::critical(this, "Module in interactive mode", "Your module is in interactive mode, please load the Sentrius programmer applicaton and retry.", QMessageBox::Close, QMessageBox::Close);
                }
                else if (baTmpBuffer.indexOf("NO") >= 0)
                {
                    //Sentrius programmer application
//                    QMessageBox::critical(this, "show me da money", "yayaya.", QMessageBox::Close, QMessageBox::Close);

                    //Connect serial signals
                    connect(&gspSerialPort, SIGNAL(readyRead()), this, SLOT(SerialRead()));
                    connect(&gspSerialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(SerialError(QSerialPort::SerialPortError)));
                    connect(&gspSerialPort, SIGNAL(bytesWritten(qint64)), this, SLOT(SerialBytesWritten(qint64)));
                    connect(&gspSerialPort, SIGNAL(aboutToClose()), this, SLOT(SerialPortClosing()));

                    //Fetch version
                    CState = Version;
                    gspSerialPort.write(COMMAND_MESSAGE_VERSION);
                    gspSerialPort.write(LINE_END_CHARACTER);
                }
                else
                {
                    //Unknown state or device
                    gspSerialPort.close();
                    QMessageBox::critical(this, "Unknown module or state", "Your module is not responding to commands, ensure you have chosen the correct options and try again.", QMessageBox::Close, QMessageBox::Close);
                }
            }
        }
        else
        {
            //Error whilst opening
            ui->statusBar->showMessage("Error: ");
            ui->statusBar->showMessage(ui->statusBar->currentMessage().append(gspSerialPort.errorString()));

            QString strMessage = tr("Error whilst attempting to open the serial device: ").append(gspSerialPort.errorString()).append("\n\nIf the serial port is open in another application, please close the other application")
#if !defined(_WIN32) && !defined( __APPLE__)
            .append(", please also ensure you have been granted permission to the serial device in /dev/")
#endif
            .append((ui->combo_Baud->currentText().toULong() > 115200 ? ", please also ensure that your serial device supports baud rates greater than 115200 (normal COM ports do not have support for these baud rates)" : ""))
            .append(" and try again.");
            QMessageBox::critical(this, "Error opening serial port", strMessage, QMessageBox::Close, QMessageBox::Close);
        }
    }
    else
    {
        //No serial port selected
        QMessageBox::critical(this, "Error opening serial port", "No serial port was selected, please select a serial port and try again.\r\nIf you see no serial ports listed, ensure your device is connected to your computer and you have the appropriate drivers installed.", QMessageBox::Close, QMessageBox::Close);
    }
}

void MainWindow::on_btn_Scan_clicked()
{
    //Starts scanning for devices
    if (CState != Idle)
    {
        //Clear up previous state
//TODO
    }
    CState = Scanning;

    //Send command to start scanning
    baRecBuffer.clear();

    gspSerialPort.write("SC\x0d");
}

void MainWindow::on_btn_ScanClear_clicked()
{
    //Clears all scanned devices
    ui->table_ScanResults->clearContents();
    int i = ui->table_ScanResults->rowCount()-1;
    while (i >= 0)
    {
        ui->table_ScanResults->removeRow(i);
        --i;
    }
}

QString MainWindow::PluralText(int i)
{
    //Appends an s for plural text
    if (i != 1)
    {
        return "s";
    }

    return "";
}

void MainWindow::on_btn_ScanExport_clicked()
{
    //Exports scanned devices to a file
    int l = ui->table_ScanResults->rowCount();
    if (l == 0)
    {
        //Nothing to save
        ui->statusBar->showMessage("Error: No scanned sensor details to save.");
    }
    else
    {
        //Prompt for output filename
        QString strOutputFilename = QFileDialog::getSaveFileName(this, "Select Log File", "", "CSV Files (*.csv);;All Files (*.*)");

        if (strOutputFilename.isNull() || strOutputFilename.isEmpty())
        {
            //Save cancelled
            ui->statusBar->showMessage("Export cancelled.");
            return;
        }

        //Attempt to open file for writing
        QFile fpOutput(strOutputFilename);
        if (!fpOutput.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            //Failed to open file for writing
            ui->statusBar->showMessage(QString("Export failed: write access to ").append(strOutputFilename).append(" denied."));
            return;
        }

        //Write header
        fpOutput.write("Dev EUI, BLE Address, RSSI,\r\n");

        //Loop through all rows
        int i = 0;
        while (i < l)
        {
            //Output details to CSV file
            fpOutput.write(QString(ui->table_ScanResults->item(i, SCAN_TABLE_COLUMN_DEV_EUI)->text()).append(", ").append(ui->table_ScanResults->item(i, SCAN_TABLE_COLUMN_BLE_ADDRESS)->text()).append(", ").append(ui->table_ScanResults->item(i, SCAN_TABLE_COLUMN_RSSI)->text()).append("").toLatin1());
            DEBUG_OUT << "> " << ui->table_ScanResults->item(i, SCAN_TABLE_COLUMN_DEV_EUI)->text() << ", " << ui->table_ScanResults->item(i, SCAN_TABLE_COLUMN_BLE_ADDRESS)->text() << ", " << ui->table_ScanResults->item(i, SCAN_TABLE_COLUMN_RSSI)->text();
            ++i;
        }

        //
        ui->statusBar->showMessage(QString("Exported ").append(QString::number(i)).append(" sensor").append(PluralText(i)).append(" to ").append(strOutputFilename).append("."));
    }
}

void MainWindow::on_btn_ConfigurationButton_clicked()
{
    //
    QString strFilename = QFileDialog::getOpenFileName(this, "Open File", "", "CSV files (*.csv);;All Files (*.*)");
    if (!strFilename.isEmpty())
    {
        QFile abc(strFilename);
        if (abc.open(QFile::ReadOnly | QFile::Text))
        {
            //File opened for reading
            while (!abc.atEnd())
            {
                QByteArray thisline = abc.readLine(300);
                if (thisline.count(',') == 7)
                {
                    //Valid line
                    int32_t a = 0;
                    int32_t b = 0;
                    int32_t c = 0;
                    b = thisline.indexOf(',', b+1);
                    int nCount = ui->table_ProgramResults->rowCount();
                    ui->table_ProgramResults->insertRow(nCount);
                    while (b > 0)
                    {
                        QTableWidgetItem *tblitmDevEUI = new QTableWidgetItem();
                        tblitmDevEUI->setText(thisline.mid(c, b-c));
                        ui->table_ProgramResults->setItem(nCount, a, tblitmDevEUI);
                        c = b+1;
                        b = thisline.indexOf(',', b+1);
                        ++a;
                    }
                    QTableWidgetItem *tblitmDevEUI = new QTableWidgetItem();
                    tblitmDevEUI->setText("Waiting");
                    ui->table_ProgramResults->setItem(nCount, a, tblitmDevEUI);
                }
                else
                {
                    //Invalid line
                }
            }
        }
        else
        {
            //File failed to open
        }
    }
}

void MainWindow::on_btn_Refresh_clicked()
{
    //Clears and refreshes the list of serial devices
    QString strPrev = "";
    QRegularExpression reTempRE("^(\\D*?)(\\d+)$");
    QList<int> lstEntries;
    lstEntries.clear();

    if (ui->combo_Port->count() > 0)
    {
        //Remember previous option
        strPrev = ui->combo_Port->currentText();
    }
    ui->combo_Port->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QRegularExpressionMatch remTempREM = reTempRE.match(info.portName());
        if (remTempREM.hasMatch() == true)
        {
            //Can sort this item
            int i = lstEntries.count()-1;
            while (i >= 0)
            {
                if (remTempREM.captured(2).toInt() > lstEntries[i])
                {
                    //Found correct order position, add here
                    ui->combo_Port->insertItem(i+1, info.portName());
                    lstEntries.insert(i+1, remTempREM.captured(2).toInt());
                    i = -1;
                }
                --i;
            }

            if (i == -1)
            {
                //Position not found, add to beginning
                ui->combo_Port->insertItem(0, info.portName());
                lstEntries.insert(0, remTempREM.captured(2).toInt());
            }
        }
        else
        {
            //Cannot sort this item
            ui->combo_Port->insertItem(ui->combo_Port->count(), info.portName());
        }
    }

    //Search for previous item if one was selected
    if (strPrev == "")
    {
        //Select first item
        ui->combo_Port->setCurrentIndex(0);
    }
    else
    {
        //Search for previous
        int i = 0;
        while (i < ui->combo_Port->count())
        {
            if (ui->combo_Port->itemText(i) == strPrev)
            {
                //Found previous item
                ui->combo_Port->setCurrentIndex(i);
                break;
            }
            ++i;
        }
    }

    //Update serial port info
    on_combo_Port_currentIndexChanged(0);
}

void MainWindow::ProcessData()
{
    //
    int nPos = baRecBuffer.indexOf(RESPONSE_MESSAGE_END);
    qDebug() << ". " << baRecBuffer.length() << ", " << baRecBuffer;
    while (nPos != -1)
    {
        //Parse command
        if (nPos <= MESSAGE_ID_LENGTH)
        {
            //Message is not long enough
            DEBUG_OUT << "Invalid message length, expected minimum " << MESSAGE_ID_LENGTH << ", got " << nPos << " (" << baRecBuffer.left(nPos) << ")";
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_ADVERT)
        {
            //Advertising packet
            //AD 01D86795539E21 -65 12345678ABCDEF55 \n"
            if (nPos != RESPONSE_MESSAGE_ADVERT_LENGTH)
            {
                //Message length is incorrect
                DEBUG_OUT << "Advertising message is wrong length, expected " << RESPONSE_MESSAGE_ADVERT_LENGTH << " got " << nPos << " (" << baRecBuffer.left(nPos) << ")";
                continue;
            }
            else if (CState != Scanning && CState != ScanningUpdate)
            {
                //Should not get this message when scanning
                DEBUG_OUT << "Got advertising message in wrong mode (" << CState << ")";
                continue;
            }

            QString strDevEUI = baRecBuffer.mid(RESPONSE_MESSAGE_ADVERT_INDEX_DEV_EUI, RESPONSE_MESSAGE_ADVERT_LENGTH_DEV_EUI);

            if (CState == Scanning)
            {
                //Split the data up
                QString strAddress = baRecBuffer.mid(RESPONSE_MESSAGE_ADVERT_INDEX_BLE_ADDRESS, RESPONSE_MESSAGE_ADVERT_LENGTH_BLE_ADDRESS);
                QString strRSSI = baRecBuffer.mid(RESPONSE_MESSAGE_ADVERT_INDEX_RSSI, RESPONSE_MESSAGE_ADVERT_LENGTH_RSSI);

                //Add it to the list of detected devices
                QTableWidgetItem *tblitmDevEUI = new QTableWidgetItem();
                QTableWidgetItem *tblitmAddress = new QTableWidgetItem();
                QTableWidgetItem *tblitmRSSI = new QTableWidgetItem();
                tblitmDevEUI->setText(strDevEUI);
                tblitmAddress->setText(strAddress);
                tblitmRSSI->setText(strRSSI);
                int nCount = ui->table_ScanResults->rowCount();
                ui->table_ScanResults->insertRow(nCount);
                ui->table_ScanResults->setItem(nCount, SCAN_TABLE_COLUMN_DEV_EUI, tblitmDevEUI);
                ui->table_ScanResults->setItem(nCount, SCAN_TABLE_COLUMN_BLE_ADDRESS, tblitmAddress);
                ui->table_ScanResults->setItem(nCount, SCAN_TABLE_COLUMN_RSSI, tblitmRSSI);

                DEBUG_OUT << "Found: " << strAddress << ", " << strDevEUI << ", " << strRSSI;
            }
            else if (CState == ScanningUpdate)
            {
                //Check if this is a device we want to update
                QList<QTableWidgetItem *> Check = ui->table_ProgramResults->findItems(strDevEUI, Qt::MatchExactly);
                qDebug() << "Got Row: " << Check.first()->row();
                qDebug() << "Got Col: " << Check.first()->column();
                qDebug() << "Got Text: " << Check.first()->text();
                if (!Check.isEmpty() && ui->table_ProgramResults->item(Check.first()->row(), 7)->text() == "Waiting")
                {
                    //Sensor needs updating, let's connect
                    ui->table_ProgramResults->item(Check.first()->row(), 7)->setText("Connecting...");
                }
            }
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_VERSION)
        {
            //Version response
            if (nPos != RESPONSE_MESSAGE_VERSION_LENGTH)
            {
                //Message length is incorrect
                DEBUG_OUT << "Version message is wrong length, expected " << RESPONSE_MESSAGE_VERSION_LENGTH << " got " << nPos << " (" << baRecBuffer.left(nPos) << ")";
                continue;
            }
            else if (CState != Version)
            {
                //Should not get this message when requesting the version
                DEBUG_OUT << "Got version message in wrong mode (" << CState << ")";
                continue;
            }

            //Extract the version
            QString strVersion = baRecBuffer.mid(RESPONSE_MESSAGE_VERSION_INDEX_VERSION, RESPONSE_MESSAGE_VERSION_LENGTH_VERSION);

            //Now in idle mode
            CState = Idle;

            //Switch to scan tab
            ui->tabcontrol_View->setCurrentIndex(1);

            //Show version in status bar
            ui->statusBar->showMessage(QString("Sentrius programmer application v").append(strVersion).append(" initialised."));
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_ON_ERROR)
        {
            //
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_GATT_READ_ERROR)
        {
            //GATT read error
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_GATT_WRITE_ERROR)
        {
            //GATT write error
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_CHAR_MISSING_ERROR)
        {
            //Required characteristic is missing
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_STATE_MACHINE_ERROR)
        {
            //State machine error
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_SCAN_ERROR)
        {
            //Scan error
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_CONNECT_ERROR)
        {
            //Connection error
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_CONNECTED_ERROR)
        {
            //
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_CONNECT)
        {
            //Connected to sensor
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_DISCONNECT)
        {
            //Disconnected from sensor
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_CONNECTION_TIMEOUT)
        {
            //Connection timeout occured
        }
/*
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_NOOP)
        {
            //No-operation response
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_UPTIME)
        {
            //Uptime response
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_ACKNOWLEDGE)
        {
            //Command acknowledged
        }
        else if (baRecBuffer.left(MESSAGE_ID_LENGTH) == RESPONSE_MESSAGE_STARTUP)
        {
            //Notification of application started
        }
*/
        baRecBuffer.remove(0, nPos+1);
        nPos = baRecBuffer.indexOf(RESPONSE_MESSAGE_END);
    }
}

void MainWindow::SerialRead()
{
    if (CState == Idle)
    {
        //In idle mode, not expecting any data
        gspSerialPort.clear(QSerialPort::Input);
        return;
    }

    //Append to receive buffer
    baRecBuffer.append(gspSerialPort.readAll());

//    if (CState == Scanning)
//    {
        //
        ProcessData();
//    }
#ifdef nope
    //Update the last received field
    ui->label_LastRx->setText(QDateTime::currentDateTime().toString("dd/MM @ hh:mm:ss"));

    //Read the data into a buffer and copy it to edit for the display data
        //Speed test is not running
        QByteArray baOrigData = gspSerialPort.readAll();

        if (ui->check_SkipDL->isChecked() == false || (gbTermBusy == false || (gbTermBusy == true && baOrigData.length() > 6) || (gbTermBusy == true && (gchTermMode == MODE_CHECK_ERROR_CODE_VERSIONS || gchTermMode == MODE_CHECK_UWTERMINALX_VERSIONS || gchTermMode == MODE_UPDATE_ERROR_CODE || gchTermMode == MODE_CHECK_FIRMWARE_VERSIONS || gchTermMode == 50))))
        {
            //Update the display with the data
            QByteArray baDispData = baOrigData;

            //Check if this should be passed to the logger
            if (ui->check_LogEnable->isChecked())
            {
                //Add to log
                gpMainLog->WriteRawLogData(baOrigData);
            }

            if (ui->check_ShowCLRF->isChecked() == true)
            {
                //Escape \t, \r and \n
                baDispData.replace("\t", "\\t").replace("\r", "\\r").replace("\n", "\\n");
            }

            //Replace unprintable characters
            baDispData.replace('\0', "\\00").replace("\x01", "\\01").replace("\x02", "\\02").replace("\x03", "\\03").replace("\x04", "\\04").replace("\x05", "\\05").replace("\x06", "\\06").replace("\x07", "\\07").replace("\x08", "\\08").replace("\x0b", "\\0B").replace("\x0c", "\\0C").replace("\x0e", "\\0E").replace("\x0f", "\\0F").replace("\x10", "\\10").replace("\x11", "\\11").replace("\x12", "\\12").replace("\x13", "\\13").replace("\x14", "\\14").replace("\x15", "\\15").replace("\x16", "\\16").replace("\x17", "\\17").replace("\x18", "\\18").replace("\x19", "\\19").replace("\x1a", "\\1a").replace("\x1b", "\\1b").replace("\x1c", "\\1c").replace("\x1d", "\\1d").replace("\x1e", "\\1e").replace("\x1f", "\\1f");
        }

        //Update number of recieved bytes
        gintRXBytes = gintRXBytes + baOrigData.length();
        ui->label_TermRx->setText(QString::number(gintRXBytes));

        if (gbTermBusy == true && gchTermMode2 == 0)
        {
            //Currently waiting for a response
            gstrTermBusyData = gstrTermBusyData.append(baOrigData);
            gchTermBusyLines = gchTermBusyLines + baOrigData.count("\n");
            if ((ui->check_CheckLicense->isChecked() && (gchTermMode == MODE_COMPILE_LOAD || gchTermMode == MODE_COMPILE_LOAD_RUN || gchTermMode == MODE_SERVER_COMPILE_LOAD || gchTermMode == MODE_SERVER_COMPILE_LOAD_RUN) && gchTermBusyLines == 6) || ((!ui->check_CheckLicense->isChecked() || !(gchTermMode == MODE_COMPILE_LOAD || gchTermMode == MODE_COMPILE_LOAD_RUN || gchTermMode == MODE_SERVER_COMPILE_LOAD || gchTermMode == MODE_SERVER_COMPILE_LOAD_RUN)) && gchTermBusyLines == 4))
            {
                //Enough data, check it.
                if (ui->check_CheckLicense->isChecked() && gchTermBusyLines == 6)
                {
                    //Check for license response
                    QRegularExpression reTempLicRE("\n10\t4\t00 ([a-zA-Z0-9]{12})\r\n00\r");
                    QRegularExpressionMatch remTempLicREM = reTempLicRE.match(gstrTermBusyData);
                    if (remTempLicREM.hasMatch() == true && remTempLicREM.captured(1).toUpper() == "0016A4C0FFEE")
                    {
                        //License is not valid, display a warning to the user
                        QString strMessage = tr("Please note: The module you are downloading to does not have a valid license and therefore some firmware functionality may not work or return unexpected error codes.\r\n\r\nTo fix this issue, please add your module license using: 'at+lic <license code>', or contact Laird Support with the module Bluetooth Address if you do not have a backup of the license code (issue the command 'at i 14' to get your module's Bluetooth address).");
                        gpmErrorForm->show();
                        gpmErrorForm->SetMessage(&strMessage);
                    }
                }
            }
        }
#endif
}

void MainWindow::on_combo_Port_currentIndexChanged(int)
{
    //Serial port selection has been changed, update text
    if (ui->combo_Port->currentText().length() > 0)
    {
        QSerialPortInfo spiSerialInfo(ui->combo_Port->currentText());
        if (!spiSerialInfo.isNull())
        {
            //Port exists
            QString strDisplayText(spiSerialInfo.description());
            if (spiSerialInfo.manufacturer().length() > 1)
            {
                //Add manufacturer
                strDisplayText.append(" (").append(spiSerialInfo.manufacturer()).append(")");
            }
            if (spiSerialInfo.serialNumber().length() > 1)
            {
                //Add serial
                strDisplayText.append(" [").append(spiSerialInfo.serialNumber()).append("]");
            }
            ui->label_SerialInfo->setText(strDisplayText);
        }
        else
        {
            //No such port
            ui->label_SerialInfo->setText("Invalid serial port selected");
        }
    }
    else
    {
        //Clear text as no port is selected
        ui->label_SerialInfo->clear();
    }
}

void
MainWindow::SerialError(
    QSerialPort::SerialPortError speErrorCode
    )
{
    if (speErrorCode == QSerialPort::NoError)
    {
        //No error. Why this is ever emitted is a mystery to me.
        return;
    }
    else if (speErrorCode == QSerialPort::ResourceError || speErrorCode == QSerialPort::PermissionError)
    {
        //Resource error or permission error (device unplugged?)
        QString strMessage = tr("Fatal error with serial connection.\nPlease reconnect to the device to continue.");
        QMessageBox::critical(this, "Error", strMessage, QMessageBox::Close, QMessageBox::Close);

        if (gspSerialPort.isOpen() == true)
        {
            //Close active connection
            gspSerialPort.close();
        }

        //Change status message
        ui->statusBar->showMessage("");

        //Change button text
//        ui->btn_TermClose->setText("&Open Port");


        //Close log file if open
//        if (gpMainLog->IsLogOpen() == true)
//        {
//            gpMainLog->CloseLogFile();
//        }

        //Show disconnection balloon
//        if (gbSysTrayEnabled == true && !this->isActiveWindow() && !gpmErrorForm->isActiveWindow())
//        {
//            gpSysTray->showMessage(ui->combo_COM->currentText().append(" Removed"), QString("Connection to device ").append(ui->combo_COM->currentText()).append(" has been lost due to disconnection."), QSystemTrayIcon::Critical);
//        }
    }
}

void MainWindow::SerialBytesWritten(qint64 intByteCount)
{
    //Updates the display with the number of bytes written
//        gintTXBytes += intByteCount;
//        ui->label_TermTx->setText(QString::number(gintTXBytes));
}

void MainWindow::SerialPortClosing()
{
    //Called when the serial port is closing
}

void MainWindow::on_btn_Programming_Start_clicked()
{
    if (CState != Idle)
    {
        //Clear up previous state
//TODO
    }
    CState = ScanningUpdate;

    //Send command to start scanning
    baRecBuffer.clear();

    gspSerialPort.write("SC\x0d");
}

void MainWindow::on_btn_Programming_Stop_clicked()
{
    CState = Idle;
}
