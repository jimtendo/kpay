/*
 *   Copyright 2010 Marco Martin <notmart@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  2.010-1301, USA.
 */

import QtQuick 2.1
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.0

/**
 * An item delegate for the primitive ListView component.
 *
 * It's intended to make all listviews look coherent.
 * It has a default icon and a label
 *
 * @inherit AbstractListItem
 */
AbstractListItem {
    id: listItem

    /**
     * string: bool
     * A single text label the list item will contain
     */
    property alias date: dateItem.text
    property alias amount: amountItem.text
    property alias value: valueItem.text
    property alias confirmations: confirmationsItem.text

    /**
     * icon: var
     * A single icon that will be displayed in the list item. The icon can
     * be either a QIcon, a string name of a fdo compatible name,
     * or any url accepted by the Image element.
     */
    property alias icon: iconItem.source

    RowLayout {
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
        Icon {
            id: iconItem
            Layout.minimumHeight: Units.iconSizes.smallMedium
            Layout.maximumHeight: Layout.minimumHeight
            Layout.minimumWidth: height
            selected: listItem.checked || listItem.pressed
        }
        Label {
            id: dateItem
            color: listItem.checked || listItem.pressed ? listItem.activeTextColor : listItem.textColor
        }
        Label {
            id: amountItem
            color: listItem.checked || listItem.pressed ? listItem.activeTextColor : listItem.textColor
        }
        Label {
            id: valueItem
            color: listItem.checked || listItem.pressed ? listItem.activeTextColor : listItem.textColor
        }
        Label {
            id: confirmationsItem
            color: listItem.checked || listItem.pressed ? listItem.activeTextColor : listItem.textColor
        }
    }
}
