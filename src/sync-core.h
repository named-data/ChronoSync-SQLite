/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2013 University of California, Los Angeles
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
 * Author: Zhenkai Zhu <zhenkai@cs.ucla.edu>
 *         Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#ifndef SYNC_CORE_H
#define SYNC_CORE_H

#include "sync-log.h"
#include <ccnx-wrapper.h>
#include <ccnx-selectors.h>
#include <scheduler.h>
#include <executor.h>
#include <task.h>

#include <boost/function.hpp>

class SyncCore
{
public:
  typedef boost::function<void (SyncStateMsgPtr stateMsg) > StateMsgCallback;

  static const int FRESHNESS = 2; // seconds
  static const string RECOVER;
  static const double WAIT; // seconds;
  static const double RANDOM_PERCENT; // seconds;

public:
  SyncCore(SyncLogPtr syncLog
           , const Ccnx::Name &userName
           , const Ccnx::Name &localPrefix      // routable name used by the local user
           , const Ccnx::Name &syncPrefix       // the prefix for the sync collection
           , const StateMsgCallback &callback   // callback when state change is detected
           , Ccnx::CcnxWrapperPtr ccnx
           , double syncInterestInterval = -1.0);
  ~SyncCore();

  void
  localStateChanged ();

  /**
   * @brief Schedule an event to update local state with a small delay
   *
   * This call is preferred to localStateChanged if many local state updates
   * are anticipated within a short period of time
   */
  void
  localStateChangedDelayed ();

  void
  updateLocalState (sqlite3_int64);

// ------------------ only used in test -------------------------
public:
  HashPtr
  root() const { return m_rootHash; }

  sqlite3_int64
  seq (const Ccnx::Name &name);

private:
  void
  handleInterest(const Ccnx::Name &name);

  void
  handleSyncData(const Ccnx::Name &name, Ccnx::PcoPtr content);

  void
  handleSyncDataExecute(const Ccnx::Name &name, Ccnx::PcoPtr content);

  void
  handleRecoverData(const Ccnx::Name &name, Ccnx::PcoPtr content);

  void
  handleRecoverDataExecute(const Ccnx::Name &name, Ccnx::PcoPtr content);

  void
  handleSyncInterestTimeout(const Ccnx::Name &name, const Ccnx::Closure &closure, Ccnx::Selectors selectors);

  void
  handleRecoverInterestTimeout(const Ccnx::Name &name, const Ccnx::Closure &closure, Ccnx::Selectors selectors);

  void
  deregister(const Ccnx::Name &name);

  void
  recover(HashPtr hash);

private:
  void
  sendSyncInterest();

  void
  handleSyncInterest(const Ccnx::Name &name);

  void
  handleRecoverInterest(const Ccnx::Name &name);

  void
  handleStateData(const Ccnx::Bytes &content);

private:
  Ccnx::CcnxWrapperPtr m_ccnx;

  SyncLogPtr m_log;
  SchedulerPtr m_scheduler;
  Executor m_executor;
  StateMsgCallback m_stateMsgCallback;

  Ccnx::Name m_syncPrefix;
  HashPtr m_rootHash;

  IntervalGeneratorPtr m_recoverWaitGenerator;

  TaskPtr m_sendSyncInterestTask;

  double m_syncInterestInterval;
};

#endif // SYNC_CORE_H
