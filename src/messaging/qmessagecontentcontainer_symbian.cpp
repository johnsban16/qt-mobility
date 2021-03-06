/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "qmessagecontentcontainer.h"
#include <QStringList>
#include <QTextCodec>
#include "qmessagecontentcontainer_symbian_p.h"
#include <qmtmengine_symbian_p.h>
#include <messagingutil_p.h>
#ifdef FREESTYLEMAILUSED
#include "qfsengine_symbian_p.h"
#endif

QTM_BEGIN_NAMESPACE

QMessageContentContainer QMessageContentContainerPrivate::from(long int messageId,
                                                               unsigned int attachmentId,
                                                               QByteArray &name,
                                                               QByteArray &mimeType,
                                                               QByteArray &mimeSubType,
#ifdef FREESTYLEMAILUSED
                                                               int size,
                                                               EmailInterface::TMessageContentId fsContentId)
#else
                                                               int size)
#endif
{
    QMessageContentContainer result;
#ifdef FREESTYLEMAILUSED
    result.d_ptr->_fsContentId = fsContentId;
#endif
    result.d_ptr->_containingMessageId = messageId;
    result.d_ptr->_attachmentId = attachmentId;
    result.d_ptr->_name = name;
    result.d_ptr->_type = mimeType;
    result.d_ptr->_subType = mimeSubType;
    result.d_ptr->_size = size;
    result.d_ptr->_available = true;
    return result;
}

QMessageContentContainerPrivate& QMessageContentContainerPrivate::operator=(const QMessageContentContainerPrivate &other)
{
    q_ptr = other.q_ptr;
    _message = other._message;
    _available = other._available;
    _size = other._size;
#ifdef FREESTYLEMAILUSED
    _contentRetrieved = other._contentRetrieved;
    _freestyleAttachment = other._freestyleAttachment;
    _fsContentId = other._fsContentId;
#endif
    _attachments = other._attachments;
    _type = other._type;
    _subType = other._subType;
    _charset = other._charset;
    _name = other._name;
    _content = other._content;
    _textContent = other._textContent;
    _filename = other._filename;
    _messageId = other._messageId;
    _id = other._id;
    _header = other._header;
    _containingMessageId = other._containingMessageId;
    _attachmentId = other._attachmentId;

    return *this;
}

bool QMessageContentContainerPrivate::isMessage() const
{
    return (_message != 0);
}

void QMessageContentContainerPrivate::setDerivedMessage(QMessage *derived)
{
    _message = derived;
}

void QMessageContentContainerPrivate::clearContents()
{
    _type = QByteArray("text");
    _subType = QByteArray("plain");
    _charset = QByteArray();
    _name = QByteArray();
    _content = QByteArray();
    _textContent = QString();
    _filename = QByteArray();
    _available = false;
    _size = 0;
#ifdef FREESTYLEMAILUSED
    _contentRetrieved = true;
    _fsContentId = EmailInterface::TMessageContentId();
#endif
    _header.clear();
    _attachments.clear();
    _containingMessageId = 0;
    _attachmentId = 0;
}

void QMessageContentContainerPrivate::setContentType(const QByteArray &type, const QByteArray &subType, const QByteArray &charset)
{
    clearContents();

    _type = type;
    _subType = subType;
    _charset = charset;
}

void QMessageContentContainerPrivate::setContent(const QString &content, const QByteArray &type, const QByteArray &subType, const QByteArray &charset)
{
    setContentType(type, subType, charset);

    _textContent = content;
    _size = content.size();
    _available = true;
}

void QMessageContentContainerPrivate::setContent(const QByteArray &content, const QByteArray &type, const QByteArray &subType, const QByteArray &charset)
{
    setContentType(type, subType, charset);

    _content = content;
    _size = content.size();
    _available = true;
}

void QMessageContentContainerPrivate::setHeaderField(const QByteArray &name, const QByteArray &value)
{
    _header.remove(name);
    _header.insert(name, value);
}

QMessageContentContainer* QMessageContentContainerPrivate::attachment(const QMessageContentContainerId &id)
{
    if (isMessage()) {
#ifdef FREESTYLEMAILUSED
        if (!_contentRetrieved) {
            CFSEngine::instance()->retrieveMessageContentHeaders(*_message);
        }
#endif
        if (id == bodyContentId()) {
            return _message;
        } else {
            foreach (const QMessageContentContainer &container, _attachments) {
                if (container.d_ptr->_id == id) {
                    return const_cast<QMessageContentContainer*>(&container);
                }
            }
        }
    }

    return 0;
}

const QMessageContentContainer* QMessageContentContainerPrivate::attachment(const QMessageContentContainerId &id) const
{
    if (isMessage()) {
#ifdef FREESTYLEMAILUSED
        if (!_contentRetrieved) {
            CFSEngine::instance()->retrieveMessageContentHeaders(*_message);
        }
#endif
        if (id == bodyContentId()) {
            return _message;
        } else {
            foreach (const QMessageContentContainer &container, _attachments) {
                if (container.d_ptr->_id == id) {
                    return &container;
                }
            }
        }
    }

    return 0;
}

bool QMessageContentContainerPrivate::createAttachment(const QString& attachmentPath)
{
    //set the attachment data

    if (!QFile::exists(attachmentPath)) {
        return false;
    }

    QFile attachmentFile(attachmentPath);
    if (!attachmentFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    _content = attachmentFile.readAll();
    _available = true;
        
    _size = attachmentFile.size();    
    
    attachmentFile.close();
    QFileInfo fi(attachmentPath);
    _name = fi.fileName().toLatin1();
    
    //set the mime-type
    QByteArray mimeType;
    RApaLsSession session;    
    QString fileString = fi.fileName();
    TPtrC16 filePtr(reinterpret_cast<const TUint16*>(fileString.utf16()));
    TBuf8<KMaxDataTypeLength> fileType;
    TPtrC8 ptr8((TUint8 *)(_content.constData()), _content.length());
    if(session.Connect() == KErrNone){                        
        TDataRecognitionResult fileDataType;                     
        session.RecognizeData(filePtr, ptr8, fileDataType);                                         
        fileType.Copy(fileDataType.iDataType.Des8());
        mimeType = QByteArray((const char*)fileType.Ptr(), fileType.Length());
        session.Close();                
    }

    int index = mimeType.indexOf("/");
    if (index != -1) {
        _type = mimeType.left(index).trimmed();
        _subType = mimeType.mid(index + 1).trimmed();
    }
    
    // set the whole filepath to _filename
    _filename = fi.filePath().toLatin1();
    
    return true;
}

QMessageContentContainerId QMessageContentContainerPrivate::appendContent(QMessageContentContainer& container)
{
#ifdef FREESTYLEMAILUSED
    if ((_message != 0) && !_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*_message);
    }
#endif
    container.d_ptr->_id = QMessageContentContainerId(SymbianHelpers::addIdPrefix(QString::number(_attachments.count()+1),SymbianHelpers::EngineTypeMTM));
    _attachments.append(container);
    return container.d_ptr->_id;
}

QMessageContentContainerId QMessageContentContainerPrivate::prependContent(QMessageContentContainer& container)
{
#ifdef FREESTYLEMAILUSED
    if ((_message != 0) && !_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*_message);
    }
#endif
    _attachments.prepend(container);
    for (int i = 0; i < _attachments.count(); ++i) {
        _attachments[i].d_ptr->_id = QMessageContentContainerId(SymbianHelpers::addIdPrefix(QString::number(i+1),SymbianHelpers::EngineTypeMTM));
    }
    return _attachments[0].d_ptr->_id;
}



QMessageContentContainerId QMessageContentContainerPrivate::bodyContentId()
{
    return QMessageContentContainerId(SymbianHelpers::addIdPrefix(QString::number(0),SymbianHelpers::EngineTypeMTM));
}

QByteArray QMessageContentContainerPrivate::attachmentFilename(const QMessageContentContainer& container)
{
    return container.d_ptr->_filename;
}

QMessageContentContainerPrivate* QMessageContentContainerPrivate::implementation(const QMessageContentContainer &container)
{
    return container.d_ptr;
}

QMessageContentContainer::QMessageContentContainer()
: d_ptr(new QMessageContentContainerPrivate(this))
{
}

QMessageContentContainer::QMessageContentContainer(const QMessageContentContainer &other)
: d_ptr(new QMessageContentContainerPrivate(this))
{
    this->operator=(other);
}

QMessageContentContainer& QMessageContentContainer::operator=(const QMessageContentContainer& other)
{
    if (&other != this) {
        *d_ptr = *other.d_ptr;
    }
    
    return *this;
}

QMessageContentContainer::~QMessageContentContainer()
{
    delete d_ptr;
}

QByteArray QMessageContentContainer::contentType() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    return d_ptr->_type;
}

QByteArray QMessageContentContainer::contentSubType() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    return d_ptr->_subType;
}

QByteArray QMessageContentContainer::contentCharset() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    return d_ptr->_charset;
}

QByteArray QMessageContentContainer::suggestedFileName() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    return d_ptr->_name;
}

bool QMessageContentContainer::isContentAvailable() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    return d_ptr->_available;
}

int QMessageContentContainer::size() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    int size = 0;
    if (d_ptr->_size != 0) {
        size = d_ptr->_size;
    } else {
        QMessageContentContainerPrivate *container(((QMessageContentContainer *)(this))->d_ptr);
        if (container->_size != 0) {
            size += container->_size;
        }
        foreach (const QMessageContentContainer &attachment, container->_attachments) {
            size += attachment.size();
        }
    }
    return size;
}

QString QMessageContentContainer::textContent() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    if (d_ptr->_textContent.isEmpty() && d_ptr->_attachmentId != 0) {
#ifdef FREESTYLEMAILUSED
        if (d_ptr->_freestyleAttachment) {
            CFSEngine* fsEngine = CFSEngine::instance();
            const_cast<QString&>(d_ptr->_textContent) = fsEngine->attachmentTextContent(d_ptr->_containingMessageId,
                                                                                        d_ptr->_fsContentId,
                                                                                        d_ptr->_charset);
            if (!d_ptr->_textContent.isEmpty() && d_ptr->_charset.isEmpty()) {
                d_ptr->_charset = QMessage::preferredCharsetFor(d_ptr->_textContent);
                if (d_ptr->_charset.isEmpty()) {
                    d_ptr->_charset = "UTF-8";
                }
            }
        } else {
            CMTMEngine* mtmEngine = CMTMEngine::instance();
            const_cast<QString&>(d_ptr->_textContent) = mtmEngine->attachmentTextContent(d_ptr->_containingMessageId, d_ptr->_attachmentId, d_ptr->_charset);
        }
#else
        CMTMEngine* mtmEngine = CMTMEngine::instance();
        const_cast<QString&>(d_ptr->_textContent) = mtmEngine->attachmentTextContent(d_ptr->_containingMessageId, d_ptr->_attachmentId, d_ptr->_charset);
#endif
    }
    if (!d_ptr->_textContent.isEmpty()) {
        return d_ptr->_textContent;
    }
    
    QTextCodec *codec = QTextCodec::codecForName(d_ptr->_charset.data());
    if (codec) {
        return codec->toUnicode(d_ptr->_content);
    } else {
        return QString::fromLatin1(d_ptr->_content);
    }
}

QByteArray QMessageContentContainer::content() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    if (d_ptr->_content.isEmpty() && d_ptr->_attachmentId != 0) {
#ifdef FREESTYLEMAILUSED
        if (d_ptr->_freestyleAttachment) {
            CFSEngine* fsEngine = CFSEngine::instance();
            const_cast<QByteArray&>(d_ptr->_content) = fsEngine->attachmentContent(d_ptr->_containingMessageId,
                                                                                   d_ptr->_fsContentId );
        } else {
            CMTMEngine* mtmEngine = CMTMEngine::instance();
            const_cast<QByteArray&>(d_ptr->_content) = mtmEngine->attachmentContent(d_ptr->_containingMessageId, d_ptr->_attachmentId);
        }
#else
        CMTMEngine* mtmEngine = CMTMEngine::instance();
        const_cast<QByteArray&>(d_ptr->_content) = mtmEngine->attachmentContent(d_ptr->_containingMessageId, d_ptr->_attachmentId);
#endif
    }

    return d_ptr->_content;
}

void QMessageContentContainer::writeTextContent(QTextStream& out) const
{
    out << textContent();
}

void QMessageContentContainer::writeContent(QDataStream& out) const
{
    QByteArray data(content());
    out.writeRawData(data.constData(), data.length());
}

QMessageContentContainerIdList QMessageContentContainer::contentIds() const
{
    QMessageContentContainerIdList ids;

#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    if (d_ptr->isMessage()) {
        foreach (const QMessageContentContainer &container, d_ptr->_attachments) {
            ids.append(container.d_ptr->_id);
        }
    }

    return ids;
}

QMessageContentContainer QMessageContentContainer::find(const QMessageContentContainerId &id) const
{
    if (d_ptr->isMessage()) {
#ifdef FREESTYLEMAILUSED
        if (!d_ptr->_contentRetrieved) {
            CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
        }
#endif
        if (const QMessageContentContainer *container = d_ptr->attachment(id)) {
            return *container;
        }
    }
    
    return QMessageContentContainer();
}

bool QMessageContentContainer::contains(const QMessageContentContainerId &id) const
{
    if (d_ptr->isMessage()) {
        return (d_ptr->attachment(id) != 0);
    }
    
    return false;
}

QString QMessageContentContainer::headerFieldValue(const QByteArray &name) const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    QMultiMap<QByteArray, QString>::const_iterator it = d_ptr->_header.find(name);
    if (it != d_ptr->_header.end()) {
        return it.value();
    }
    
    return QString();
}

QStringList QMessageContentContainer::headerFieldValues(const QByteArray &name) const
{
    QStringList values;

#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    QMultiMap<QByteArray, QString>::const_iterator it = d_ptr->_header.find(name);
    while ((it != d_ptr->_header.end()) && (it.key() == name)) {
        values.append(it.value());
        ++it;
    }

    return values;
}

QList<QByteArray> QMessageContentContainer::headerFields() const
{
#ifdef FREESTYLEMAILUSED
    if ((d_ptr->_message != 0) && !d_ptr->_contentRetrieved) {
        CFSEngine::instance()->retrieveMessageContentHeaders(*d_ptr->_message);
    }
#endif
    return d_ptr->_header.keys();
}

void QMessageContentContainer::setDerivedMessage(QMessage *derived)
{
    d_ptr->setDerivedMessage(derived);
}

QTM_END_NAMESPACE
