// Copyright (c) 2015-2019 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef PMLOGLIB_CXX_H_INCLUDED
#define PMLOGLIB_CXX_H_INCLUDED

#pragma once

#include "PmLogLib.h"
#include <string>
#include <memory>

namespace pmlog
{

class PmLog
{
    PmLogContext context_;

public:
    class Stream
    {
        PmLogContext parent_ctx_;
        std::string msgId_;
        PmLogLevel level_;
        bool flushed_;
        PmLogErr err_;
        std::string messages_;
        std::string kvpairs_;
    public:
        Stream(PmLogContext context, const std::string& msgId, PmLogLevel level);
        ~Stream();

        template <typename T>
        Stream& operator << (T e)
        {
            flushed_ = false;
            put(e);
            return *this;
        }

        Stream& operator << (void (*manipulator)(PmLog::Stream*))
        {
            manipulator(this);
            return *this;
        }

        PmLogErr errorState() const;
        void flush();
    private:
        void put(const std::pair<std::string, std::string>& kv);
        void put(const std::pair<std::string, int>& kv);
        void put(const std::string& txt);
        void put(int num);
        void clear();
    };

    struct DummyStream
    {
        template <typename T> DummyStream& operator << (T) { return *this; }
        PmLogErr errorState() const { return kPmLogErr_None; }
    };

public:
    PmLog(const std::string& ctxName = "");
    PmLog(const PmLog&) = delete;
    PmLog(PmLog&&) = delete;

    PmLog & operator=(const PmLog&)=delete;
    PmLog & operator=(const PmLog&&)=delete;

    Stream critical(const std::string& msgId = "DEFAULT");
    Stream error(const std::string& msgId    = "DEFAULT");
    Stream warning(const std::string& msgId  = "DEFAULT");
    Stream info(const std::string& msgId     = "DEFAULT");
    Stream debug(const std::string& msgId    = "DEFAULT");

    static std::string formatError(PmLogErr err);
};

void flush(PmLog::Stream* stream);

} // namespace pmlog

#endif // PMLOGLIB_CXX_H_INCLUDED
