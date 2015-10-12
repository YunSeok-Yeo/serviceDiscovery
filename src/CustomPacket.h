//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CustomPacket_H_
#define CustomPacket_H_

#include <omnetpp.h>
#include <simkerneldefs.h>
#include <string>

class cCommBuffer;

#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)

#endif

#define QUERY 0
#define REPLY 1
#define NOTICE 2
#define RETRANSMIT 3
#define HELLO 4
#define REGISTER 5
#define APSERVICE 9999
#define DNSSERVICE 9998

using namespace std;
class CustomPacket : public ::cPacket
{
  protected:
    int type;                   //message type
    int sequenceNum;
    int sourceId;
    int destinationId;
    int maxHopCount;
    int destinationService;
    int proxyId;
    int originSourceId;
    int originSourceSeqNum;
    string lastHop;
    int location;
    int hopCount;

  private:
    void copy(const CustomPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CustomPacket&);

  public:
    CustomPacket(const char *name=NULL, int kind=0);
    CustomPacket(const CustomPacket& other);

    virtual ~CustomPacket();
    CustomPacket& operator=(const CustomPacket& other);
    virtual CustomPacket *dup() const {return new CustomPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int GetType() const;
    virtual void SetType(int source);
    virtual int GetSource() const;
    virtual void SetSource(int source);
    virtual int GetDestination() const;
    virtual void SetDestination(int destination);
    virtual int GetMaxHopCount() const;
    virtual void SetMaxHopCount(int maxhopCount);
    virtual int GetSeqNum() const;
    virtual void SetSeqNum(int seqNum);
    virtual int GetDestinationService() const;
    virtual void SetDestinationService(int desService);
    virtual int GetProxy() const;
    virtual void SetProxy(int proxy);
    virtual int GetOriginSourceId() const;
    virtual void SetOriginSourceId(int originSourceId);
    virtual int GetOriginSourceSeqNum() const;
    virtual void SetOriginSourceSeqNum(int originSourceSeqNum);
    virtual string GetLastHop() const;
    virtual void SetLastHop(string lastHop);
    virtual int GetLocation() const;
    virtual void SetLocation(int location);
    virtual int GetHopCount() const;
    virtual void SetHopCount(int hopCount);
};

inline void doPacking(cCommBuffer *b, CustomPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, CustomPacket& obj) {obj.parsimUnpack(b);}


#endif /* CustomPacket_H_ */
