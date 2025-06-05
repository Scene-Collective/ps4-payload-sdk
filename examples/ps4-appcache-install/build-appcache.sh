#!/bin/bash
set -e
if [ -e sql/ApplicationCache.sql ]
then
    sqlite3 sql/ApplicationCache.db < sql/ApplicationCache.sql
    base64 -w 0 sql/ApplicationCache.db > sql/ApplicationCache.b64
    echo 'static const unsigned char ApcStr[] = "'$(cat sql/ApplicationCache.b64)'";' > include/ApplicationCache.h
    rm -f sql/ApplicationCache.b64
	rm -f sql/ApplicationCache.db
fi
