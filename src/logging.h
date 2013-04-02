/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 *	   Zhenkai Zhu <zhenkai@cs.ucla.edu>
 */

#ifndef LOGGING_H
#define LOGGING_H

#include "config.h"

#ifdef HAVE_LOG4CXX

#include <log4cxx/logger.h>

#define MEMBER_LOGGER                           \
  static log4cxx::LoggerPtr staticModuleLogger;

#define INIT_MEMBER_LOGGER(className,name)          \
  log4cxx::LoggerPtr className::staticModuleLogger =  log4cxx::Logger::getLogger (name);

#define INIT_LOGGER(name) \
  static log4cxx::LoggerPtr staticModuleLogger = log4cxx::Logger::getLogger (name);

#define _LOG_DEBUG(x) \
  LOG4CXX_DEBUG(staticModuleLogger, x);

#define _LOG_TRACE(x) \
  LOG4CXX_TRACE(staticModuleLogger, x);

#define _LOG_FUNCTION(x) \
  LOG4CXX_TRACE(staticModuleLogger, __FUNCTION__ << "(" << x << ")");

#define _LOG_FUNCTION_NOARGS \
  LOG4CXX_TRACE(staticModuleLogger, __FUNCTION__ << "()");

#define _LOG_ERROR(x) \
  LOG4CXX_ERROR(staticModuleLogger, x);

#define _LOG_ERROR_COND(cond,x) \
  if (cond) { _LOG_ERROR(x) }

#define _LOG_DEBUG_COND(cond,x) \
  if (cond) { _LOG_DEBUG(x) }

void
INIT_LOGGERS ();

#else // else HAVE_LOG4CXX

#define INIT_LOGGER(name)
#define _LOG_FUNCTION(x)
#define _LOG_FUNCTION_NOARGS
#define _LOG_TRACE(x)
#define INIT_LOGGERS(x)
#define _LOG_ERROR(x)
#define _LOG_ERROR_COND(cond,x)
#define _LOG_DEBUG_COND(cond,x)

#define MEMBER_LOGGER
#define INIT_MEMBER_LOGGER(className,name)

#ifdef _DEBUG

#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

#define _LOG_DEBUG(x) \
  std::clog << boost::get_system_time () << " " << boost::this_thread::get_id () << " " << x << std::endl;

#else
#define _LOG_DEBUG(x)
#endif

#endif // HAVE_LOG4CXX

#endif // LOGGING_H
