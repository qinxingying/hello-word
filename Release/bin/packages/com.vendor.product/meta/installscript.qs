/**************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
**
** $QT_END_LICENSE$
**
**************************************************************************/

function Component()
{
    // constructor
    component.loaded.connect(this, Component.prototype.loaded);
    if (!installer.addWizardPage(component, "Page", QInstaller.TargetDirectory))
        console.log("Could not add the dynamic page.");

    installer.finishButtonClicked.connect(this, openRegisteredFileIfChecked);
    component.unusualFileType = generateUnusualFileType(5)
}

Component.prototype.isDefault = function()
{
    // select the component by default
    return true;
}

Component.prototype.createOperations = function()
{
    try {
        // call the base create operations function
        component.createOperations();

        if (systemInfo.productType === "windows") {
            component.addOperation("CreateShortcut", "@TargetDir@/PhascanView-1.1.4.exe", "@StartMenuDir@/PhascanView-1.1.4.lnk",
                "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/app.ico",
                "iconId=doppler");
        }

        if (installer.value("os") === "win") {
            var iconId = 0;
            var notepadPath = installer.environmentVariable("SystemRoot") + "\\PhascanView-1.1.4.exe";
            component.addOperation("RegisterFileType",
                                   component.unusualFileType,
                                   notepadPath + " '%1'",
                                   "PhascanView-1.1.4",
                                   "text/plain",
                                   notepadPath + "," + iconId,
                                   "ProgId=Phascan.PhascanView." + component.unusualFileType);
        }
        component.fileWithRegisteredType = installer.value("TargetDir") + "/registeredfile." + component.unusualFileType
        component.addOperation("Move", "@TargetDir@/registeredfile", component.fileWithRegisteredType);
    } catch (e) {
        console.log(e);
    }
}

Component.prototype.loaded = function ()
{
    var page = gui.pageByObjectName("DynamicPage");
    if (page != null) {
        console.log("Connecting the dynamic page entered signal.");
        page.entered.connect(Component.prototype.dynamicPageEntered);
    }
}

Component.prototype.dynamicPageEntered = function ()
{
    var pageWidget = gui.pageWidgetByObjectName("DynamicPage");
    if (pageWidget != null) {
        console.log("Setting the widgets label text.")
        pageWidget.m_pageLabel.text = "This is a dynamically created page.";
    }
}

generateUnusualFileType = function(length)
{
    var randomString = "";
    var possible = "abcdefghijklmnopqrstuvwxyz0123456789";

    for (var i = 0; i < length; i++)
        randomString += possible.charAt(Math.floor(Math.random() * possible.length));
    return randomString;
}

openRegisteredFileIfChecked = function()
{
    if (!component.installed)
        return;

    if (installer.value("os") == "win" && installer.isInstaller() && installer.status == QInstaller.Success) {
        var isOpenRegisteredFileChecked = component.userInterface("OpenFileCheckBoxForm").OpenRegisteredFileCheckBox.checked;
        if (isOpenRegisteredFileChecked) {
            QDesktopServices.openUrl("file:///" + component.fileWithRegisteredType);
        }
    }
}

