/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
// Copyright (c) 2008 Roberto Raggi <roberto.raggi@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef CPLUSPLUS_MEMORYPOOL_H
#define CPLUSPLUS_MEMORYPOOL_H

#include "CPlusPlusForwardDeclarations.h"
#include <new>

namespace CPlusPlus {

class CPLUSPLUS_EXPORT MemoryPool
{
    MemoryPool(const MemoryPool &other);
    void operator =(const MemoryPool &other);

public:
    MemoryPool();
    ~MemoryPool();

    bool initializeAllocatedMemory() const;
    void setInitializeAllocatedMemory(bool initializeAllocatedMemory);

    inline void *allocate(size_t size)
    {
        size = (size + 7) & ~7;
        if (ptr && (ptr + size < end)) {
            void *addr = ptr;
            ptr += size;
            return addr;
        }
        return allocate_helper(size);
    }

    struct State
    {
        char *ptr;
        char *end;
        int blockCount;

        inline bool isValid() const
        { return ptr != 0; }

        inline State(char *ptr = 0, int blockCount = 0)
            : ptr(ptr), blockCount(blockCount) {}
    };

    State state() const;
    void rewind(const State &state);

private:
    void *allocate_helper(size_t size);

private:
    bool _initializeAllocatedMemory;
    char **_blocks;
    int _allocatedBlocks;
    int _blockCount;
    char *ptr, *end;

    enum
    {
        BLOCK_SIZE = 8 * 1024,
        DEFAULT_BLOCK_COUNT = 8
    };
};

class CPLUSPLUS_EXPORT Managed
{
    Managed(const Managed &other);
    void operator = (const Managed &other);

public:
    Managed();
    virtual ~Managed();

    void *operator new(size_t size, MemoryPool *pool);
    void operator delete(void *);
    void operator delete(void *, MemoryPool *);
};

} // end of namespace CPlusPlus


#endif // CPLUSPLUS_MEMORYPOOL_H