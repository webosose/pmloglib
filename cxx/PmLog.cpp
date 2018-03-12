// Copyright (c) 2015-2018 LG Electronics, Inc.
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

#include "PmLog.h"
#include <utility>
#include <string>

namespace pmlog
{

PmLog::PmLog(const std::string& ctxName)
{
    PmLogGetContext(ctxName.c_str(), &context_);
}

PmLog::Stream PmLog::critical(const std::string& msgId)
{
#if defined(PMLOGLIB_ENABLE_LOGGING)
    return Stream(context_, msgId, kPmLogLevel_Critical);
#else
    return DummyStream();
#endif
}

PmLog::Stream PmLog::error(const std::string& msgId)
{
#if defined(PMLOGLIB_ENABLE_LOGGING)
    return Stream(context_, msgId, kPmLogLevel_Error);
#else
    return DummyStream();
#endif
}

PmLog::Stream PmLog::warning(const std::string& msgId)
{
#if defined(PMLOGLIB_ENABLE_LOGGING)
    return Stream(context_, msgId, kPmLogLevel_Warning);
#else
    return DummyStream();
#endif
}

PmLog::Stream PmLog::info(const std::string& msgId)
{
#if defined(PMLOGLIB_ENABLE_LOGGING)
    return Stream(context_, msgId, kPmLogLevel_Info);
#else
    return DummyStream();
#endif
}

PmLog::Stream PmLog::debug(const std::string& msgId)
{
#if defined(PMLOGLIB_ENABLE_LOGGING)
    return Stream(context_, msgId, kPmLogLevel_Debug);
#else
    return DummyStream();
#endif
}

std::string PmLog::formatError(PmLogErr err)
{
    return PmLogGetErrDbgString(err);
}

PmLog::Stream::Stream(PmLogContext context, const std::string& msgId, PmLogLevel level)
    : parent_ctx_(context)
    , msgId_(msgId)
    , level_(level)
    , flushed_(false)
    , err_(kPmLogErr_None)
{
}

PmLog::Stream::~Stream()
{
    flush();
}

void PmLog::Stream::put(const std::pair<std::string, std::string>& kv)
{
    if (!kvpairs_.empty())
    {
        kvpairs_.push_back(',');
    }

    kvpairs_.append("\"" + kv.first + "\":\"" + kv.second + "\"");
}

void PmLog::Stream::put(const std::pair<std::string, int>& kv)
{
    if (!kvpairs_.empty())
    {
        kvpairs_.push_back(',');
    }

    kvpairs_.append("\"" + kv.first + "\":" + std::to_string(kv.second));
}

void PmLog::Stream::put(const std::string& txt)
{
    messages_.append(txt);
}

void PmLog::Stream::put(int num)
{
    messages_.append(std::to_string(num));
}

void PmLog::Stream::clear()
{
    kvpairs_.clear();
    messages_.clear();
}

void PmLog::Stream::flush()
{
    if (flushed_)
    {
        return;
    }

    flushed_ = true;

    if (!PmLogIsEnabled(parent_ctx_, level_))
    {
        err_ = kPmLogErr_LevelDisabled;
    }
    else if (level_ == kPmLogLevel_Debug)
    {
        err_ = PmLogString_(parent_ctx_, level_, nullptr, nullptr, messages_.c_str());
    }
    else
    {
        err_ = PmLogString_(
            parent_ctx_, level_,
            msgId_.c_str(), ("{" + kvpairs_ + "}").c_str(), messages_.c_str());
    }

    clear();
}

PmLogErr PmLog::Stream::errorState() const
{
    return err_;
}

void flush(PmLog::Stream* stream)
{
    stream->flush();
}

} // namespace pmlog
