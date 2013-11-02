/******************************************************************************
    QtAV:  Media play library based on Qt and FFmpeg
    Copyright (C) 2013 Wang Bin <wbsecg1@gmail.com>

*   This file is part of QtAV

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#ifndef QTAV_FRAME_H
#define QTAV_FRAME_H

#include <QtAV/QtAV_Global.h>
#include <QtCore/QVariant>

// TODO: plane=>channel
namespace QtAV {

class FramePrivate;
class Q_AV_EXPORT Frame
{
    DPTR_DECLARE_PRIVATE(Frame)
public:
    virtual ~Frame() = 0;

    /*!
     * \brief bytesPerLine
     *  a decoded frame can be packed and planar. packed format has only 1 plane, while planar
     *  format has more than 1 plane. For audio, the number plane equals channel count. For
     *  video, rgb is 1 plane, yuv420p is 3 plane, p means planar
     * \param plane default is the first plane
     * \return
     */
    int planeCount() const;
    virtual int bytesPerLine(int plane = 0) const;
    // deep copy the data
    QByteArray data(int plane = 0) const;
    uchar* bits(int plane = 0);
    const uchar *bits(int plane = 0) const;
    /*!
     * \brief setBits set slice from FFmpeg
     * \param b slice
     * \param plane color/audio channel
     */
    void setBits(uchar* b, int plane = 0);
    void setBits(const QVector<uchar*>& b);
    /*
     * It's used now until I complete all pixel formats in QtAV.
     * set strides from FFmpeg. 4 channels at most for video
     */
    void setBytesPerLine(int lineSize, int plane = 0);
    void setBytesPerLine(const QVector<int>& lineSize);

    QVariantMap availableMetaData() const;
    QVariant metaData(const QString& key) const;
    void setMetaData(const QString &key, const QVariant &value);

protected:
    Frame(FramePrivate &d);
    DPTR_DECLARE(Frame)
//    QExplicitlySharedDataPointer<QVideoFramePrivate> d;
};

} //namespace QtAV

#endif // QTAV_FRAME_H
