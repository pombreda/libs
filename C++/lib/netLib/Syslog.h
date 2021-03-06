#ifndef SYSLOG_HH
#define SYSLOG_HH

#include <syslog.h>

class Syslog
{
public:
   Syslog(const char *ident);
   ~Syslog();
   Syslog& operator<<(const char*);
   Syslog& operator<<(char);
   Syslog& operator<<(short);
   Syslog& operator<<(int);
   Syslog& operator<<(long);
   Syslog& operator<<(Syslog& (*f)(Syslog&));
   void flush(const char*);
   void setPty(int);

private:
   int pty;
   char buffer[10240];
};

inline
void Syslog::setPty(int aValue)
{
   pty = aValue;
}

inline
Syslog& Syslog::operator<<(Syslog& (*f)(Syslog&))
{
   return f(*this);
}

// manipulators

inline
Syslog& endl(Syslog& lg)
{
   lg.flush("\n");
   return lg;
}

inline
Syslog& logInfo(Syslog& lg)
{
   lg.setPty(LOG_INFO);
   lg.flush("\n");
   return lg;
}

inline
Syslog& logWarning(Syslog& lg)
{
   lg.setPty(LOG_WARNING);
   lg.flush("\n");
   return lg;
}

inline
Syslog& logErr(Syslog& lg)
{
   lg.setPty(LOG_ERR);
   lg.flush("\n");
   return lg;
}

#endif //SYSLOG_HH
