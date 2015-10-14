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

#include <carray.h>
#include <cdisplaystring.h>
#include <cenvir.h>
#include <clistener.h>
#include <cmsgpar.h>
#include <cobjectfactory.h>
#include <cownedobject.h>
#include <cregistrationlist.h>
#include <csimulation.h>
#include <Compat.h>
#include <distrib.h>
#include <Ieee802Ctrl_m.h>
#include <onstartup.h>
#include <PortableDevice.h>
#include <regmacros.h>
#include <simutil.h>
#include <stddef.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>

Define_Module(PortableDevice);

/*
 *  Generate device ID and its own services.
 *
 *  And make Hello packet.
 *
 *  CustomPacket is customized version of cMessage
 */
simsignal_t PortableDevice::sentPkSignal = registerSignal("sentPk");
simsignal_t PortableDevice::rcvdPkSignal = registerSignal("rcvdPk");


void PortableDevice::initialize()
{
    currentState = 0;
    seqNum = 0;
    sendTime = 0;
    isFirst = false;
    ID = getId();
    if(strcmp(getParentModule()->getFullName(), "WirelessNode[99]") == 0){
        Service = 50;
    }else
        Service = intuniform(0, SERVICENUM - 1);
    MacAddress.setAddress(getParentModule()->getSubmodule("wlan")->getSubmodule("mac")->par("address"));
    int APs = getParentModule()->getParentModule()->par("APs");

    hello = GeneratePacket("hello", BROADCAST, 0, HELLO, 1);
    nodeRegister = GeneratePacket("nodeRegister", BROADCAST, APSERVICE, REGISTER, 10);
    query =  GeneratePacket("query", BROADCAST, 50, QUERY, 2);

    helloTimer = new CustomPacket("helloTimer");
    registerTimer = new CustomPacket("registerTimer");
    queryTimer = new CustomPacket("queryTimer");
    waitTimer = NULL;

    query->SetLocation(intuniform(0, APs));

    string s;
    stringstream out;
    out << ID <<"," << Service << "|";
    s = out.str();
    hello->SetLastHop(s);
    nodeRegister->SetLastHop(s);
    query->SetLastHop(s);



    scheduleAt(uniform(1, 5), helloTimer);
    if(APs != 0){
        scheduleAt(uniform(10, 15), registerTimer);
    }else{
        delete registerTimer;
        delete nodeRegister;
    }



    if( strcmp(getParentModule()->getFullName(), "WirelessNode[0]") == 0)
    {
        scheduleAt(uniform(20, 25), queryTimer);
    }
    else
    {
        delete queryTimer;
        delete query;
    }

}

void PortableDevice::UpdateTables(string lastHop, string macAddress, int hopCount){

    string token, secondToken;
    size_t pos, secondPos;
    string delimiter = "|", secondDelimiter = ",";
    while ((pos = lastHop.find(delimiter)) != string::npos) {

        token = lastHop.substr(0, pos);

        secondPos = token.find(secondDelimiter);
        secondToken = token.substr(0, secondPos);

        int id = atoi(secondToken.c_str());

        token.erase(0, secondPos + secondDelimiter.length());

        routingTable.UpdateEntry(id, macAddress, hopCount--);
        nodeTable.UpdateEntry(id, atoi(token.c_str()), 0, 10);

        lastHop.erase(0, pos + delimiter.length());
    }


}
void PortableDevice::UpdateRoutingTable(string routingInfo, string macAddress){
    string token, secondToken;
    size_t pos, secondPos;
    string delimiter = "|", secondDelimiter = ",";
    while ((pos = routingInfo.find(delimiter)) != string::npos) {

        token = routingInfo.substr(0, pos);

        secondPos = token.find(secondDelimiter);
        secondToken = token.substr(0, secondPos);

        token.erase(0, secondPos + secondDelimiter.length());

        int id = atoi(secondToken.c_str());
        int hopCount = atoi(token.c_str()) + 1;

        routingTable.UpdateEntry(id, macAddress, hopCount);

        routingInfo.erase(0, pos + delimiter.length());
    }

}
void PortableDevice::UpdateNodeTable(string nodeInfo){
    string token, secondToken;
    size_t pos, secondPos;
    string delimiter = "|", secondDelimiter = ",";
    while ((pos = nodeInfo.find(delimiter)) != string::npos) {

        token = nodeInfo.substr(0, pos);

        secondPos = token.find(secondDelimiter);
        secondToken = token.substr(0, secondPos);

        token.erase(0, secondPos + secondDelimiter.length());



        int id = atoi(secondToken.c_str());
        int service = atoi(token.c_str());

        nodeTable.UpdateEntry(id, service, 0, 10);

        nodeInfo.erase(0, pos + delimiter.length());
    }

}
void PortableDevice::handleMessage(cMessage *msg)
{
    CustomPacket *packet = check_and_cast<CustomPacket *>(msg);


    if(msg->isSelfMessage())
    {
        if(msg == helloTimer){
            currentState = HELLO;

            forwardMessage(hello);
            UpdateDisplay();
        }
        else if(msg == registerTimer)
        {
            int targetId = nodeTable.FindService(APSERVICE);


            currentState = REGISTER;
            nodeRegister->SetDestination(targetId != -1 ? targetId : BROADCAST);
            nodeRegister->setKind(3);

            forwardMessage(nodeRegister);
        }
        else if(strcmp(msg->getName(), "timeOut") == 0)
        {
            if(currentState == QUERY)
            {
                EV << "yys timeout ID: " << ID  << endl;
                queryBroadcastState.clear();
                currentState = -1;
            }
        }
        else if(strcmp(msg->getName(), "waitTimer") == 0)
        {
            map<int, CustomPacket *>::iterator it = waitMap.find(packet->GetSource());
            CustomPacket *retransmit = (CustomPacket *)it->second;
            waitMap.erase(it);

            if(currentState != -1)
                forwardMessage(retransmit);
            else
                delete retransmit;
        }
        else
        {
                if(nodeTable.FindService(query->GetDestinationService()) == -1 && query->GetDestinationService() != Service)
                {

                    //timeOut = new CustomPacket("timeOut");
                    //scheduleAt(simTime().dbl() + 2, timeOut);
                    // This is selfMessage

                    currentState = QUERY;
                    query->SetDestination(BROADCAST);
                    query->SetDestinationService(50);

                    sendTime = simTime();
                    forwardMessage(query);
                }
                else
                {
                    EV << "yys success time: "<< 0 << endl;;
                    currentState = -1;
                    delete query;
                }

            //}
        }



        delete packet;

        UpdateDisplay();

        return;
    }

    emit(rcvdPkSignal, msg);

    if(cache.checkEntry(packet->GetSource(), packet->GetSeqNum()) ||
            (packet->GetOriginSourceId() != 0 ? cache.checkEntry(packet->GetOriginSourceId(), packet->GetOriginSourceSeqNum()): false))
    {
        //This node already forward this message
        delete packet;
        return;
    }

    Ieee802Ctrl *ctrl = check_and_cast<Ieee802Ctrl *>(packet->getControlInfo());

    packet->SetHopCount(packet->GetHopCount() + 1);
    packet->SetMaxHopCount(packet->GetMaxHopCount() - 1);

    //Update it's tables (Routing, Node) and cache
    UpdateTables(packet->GetLastHop(), ctrl->getSrc().str(), packet->GetHopCount());
    if(packet->GetOriginSourceId() != 0)
        cache.AddEntry(packet->GetOriginSourceId(), packet->GetOriginSourceSeqNum());
    else
        cache.AddEntry(packet->GetSource(), packet->GetSeqNum());


    switch(packet->GetType()){
    case QUERY:
        Query(packet);
        break;
    case REPLY:
        Reply(packet);
        break;
    case NOTICE:
        Notice(packet);
        break;
    case RETRANSMIT:
        Retransmit(packet);
        break;
    case HELLO:
        Hello(packet);
        break;
    case REGISTER:
        Register(packet);
        break;
    default:
        delete packet;
        break;
    }
}
void PortableDevice::Register(CustomPacket *packet){

    if(packet->GetMaxHopCount() <= 0)
    {
        CustomPacket *notice = GeneratePacket("notice", packet->GetSource(), packet->GetDestinationService(), NOTICE, packet->GetHopCount());
        stringstream out;

        out << ID << "," << Service << "|";
        notice->SetLastHop(out.str());
        notice->SetOriginSourceSeqNum(packet->GetSeqNum());
        notice->setKind(1);

        forwardMessage(notice);
        delete packet;
    }
    else
    {
        string lastHop = packet->GetLastHop();


        //Now it should forward packet to proper neighbors
        //Check whether there is route or not for specific service
        stringstream out;

        //Add its service information
        out << lastHop << ID << "," << Service << "|";
        lastHop = out.str();
        packet->SetLastHop(lastHop);

        if(packet->GetDestination() == BROADCAST){
            int targetId = nodeTable.FindService(APSERVICE);
            packet->SetDestination(targetId != -1 ? targetId : BROADCAST);
        }

        forwardMessage(packet);
    }
}
void PortableDevice::Hello(CustomPacket *packet){
    CustomPacket *reply = GeneratePacket("reply", packet->GetSource(), 0, REPLY, 1);
    stringstream out;

    out << ID << "," << Service << "|";
    reply->SetLastHop(out.str());

    cMsgPar *nodeInfo = new cMsgPar("nodeInfo");
    cMsgPar *routingInfo = new cMsgPar("routingInfo");
    nodeInfo->setStringValue(nodeTable.GetEntries().c_str());
    routingInfo->setStringValue(routingTable.GetEntries().c_str());
    reply->addPar(nodeInfo);
    reply->addPar(routingInfo);
    reply->setKind(0);

    forwardMessage(reply);
    delete packet;
}
void PortableDevice::Retransmit(CustomPacket *packet){

    if(packet->GetProxy() != ID)
    {
        stringstream out;
        out << packet->GetLastHop() << ID << "," << Service << "|";
        packet->SetLastHop(out.str());

        forwardMessage(packet);
    }
    else
    {
        CustomPacket *replace = GeneratePacket("replace", /*packet->GetDestination()*/ BROADCAST, packet->GetDestinationService(), QUERY, packet->GetHopCount()+packet->GetMaxHopCount() + 2);
        stringstream out;

        out << packet->GetLastHop() << ID << "," << Service << "|";
        replace->SetLastHop(out.str());
        replace->SetOriginSourceId(packet->GetSource());
        replace->SetOriginSourceSeqNum(packet->GetOriginSourceSeqNum());
        replace->SetHopCount(packet->GetHopCount()+packet->GetMaxHopCount());

        EV << "yys broadcast" << endl;

        forwardMessage(replace);
        delete packet;
    }
}
void PortableDevice::Notice(CustomPacket *packet){

    if(packet->GetDestination() != ID)
    {
        stringstream out;
        out << packet->GetLastHop() << ID << "," << Service << "|";
        packet->SetLastHop(out.str());

        forwardMessage(packet);
    }
    else
    {
        if(packet->getKind() == 2 && currentState != -1){
            //cancelAndDelete(timeOut);

            //timeOut = new CustomPacket("timeOut");
            //scheduleAt(simTime().dbl() + 2 *(1 + packet->GetHopCount()), timeOut);

            if(!isFirst){
                isFirst = true;
                //basicDuration = simTime() - sendTime;
                basicDuration = 0.5;
            }

            if(CheckPathBeforeBroadcast(packet->GetLastHop(), packet->GetHopCount())){
                CustomPacket *retransmit = GeneratePacket("retransmit", /*packet->GetSource()*/ BROADCAST, packet->GetDestinationService(), RETRANSMIT, packet->GetHopCount()+packet->GetMaxHopCount());
                stringstream out;
                out << ID << "," << Service << "|";
                retransmit->SetLastHop(out.str());
                retransmit->SetProxy(packet->GetSource());
                retransmit->SetOriginSourceSeqNum(packet->GetOriginSourceSeqNum());

                waitMap.insert(std::pair<int, CustomPacket *>(packet->GetSource(), retransmit));

                waitTimer = new CustomPacket("waitTimer");
                waitTimer->SetSource(packet->GetSource());
                EV << "yys HopCount: " << packet->GetHopCount()+packet->GetMaxHopCount() << endl;
                scheduleAt(simTime() + basicDuration * (packet->GetHopCount()+packet->GetMaxHopCount() + 1), waitTimer); //forwardMessage(retransmit);
            }
        }

        delete packet;
    }
}
bool PortableDevice::CheckPathBeforeBroadcast(string lastHop, int hopCount)
{
    int checkLen = (hopCount + 2) / 2; //2: 2, 6: 4, 14: 8....


    list<int> tmp;
    string token, secondToken;
    size_t pos, secondPos;
    string delimiter = "|", secondDelimiter = ",";
    while ((pos = lastHop.find(delimiter)) != string::npos && checkLen-- > 0) {

        token = lastHop.substr(0, pos);

        secondPos = token.find(secondDelimiter);
        secondToken = token.substr(0, secondPos);

        token.erase(0, secondPos + secondDelimiter.length());

        int id = atoi(secondToken.c_str());
        //int service = atoi(token.c_str());
        tmp.push_back(id);
        for( list< int >::iterator iterPos = queryBroadcastState.begin(); iterPos != queryBroadcastState.end(); ++iterPos )
        {
          if(*iterPos == id)
          {
              return false;
          }
        }
        lastHop.erase(0, pos + delimiter.length());
    }

    queryBroadcastState.insert(queryBroadcastState.end(), tmp.begin(), tmp.end());

    return true;
}
void PortableDevice::Reply(CustomPacket *packet){
    if(packet->GetDestination() != ID)
    {
        stringstream out;
        out << packet->GetLastHop() << ID << "," << Service << "|";
        packet->SetLastHop(out.str());

        forwardMessage(packet);
    }
    else
    {
        // 0: hello, 1: register, 2: query
        int kind = packet->getKind();
        if(kind == 0){
            cArray arr = packet->getParList();

            cMsgPar *nodeInfo = (cMsgPar *)arr[arr.find("nodeInfo")];
            cMsgPar *routingInfo = (cMsgPar *)arr[arr.find("routingInfo")];

            Ieee802Ctrl *ctrl = check_and_cast<Ieee802Ctrl *>(packet->getControlInfo());

            UpdateRoutingTable(routingInfo->stringValue(), ctrl->getSrc().str());
            UpdateNodeTable(nodeInfo->stringValue());

            arr.remove(nodeInfo);
            arr.remove(routingInfo);
            delete nodeInfo;
            delete routingInfo;

        }else if(kind == 2 && currentState != -1){
            //cancelAndDelete(timeOut);
            EV << "yys success time: " << simTime() - sendTime << endl;
            queryBroadcastState.clear();
            currentState = -1;
        }
        UpdateDisplay();
        delete packet;
    }
}
CustomPacket* PortableDevice::GeneratePacket(const char* name, int destinationId, int destinationService, int type, int maxHopCount){

    cache.AddEntry(ID, seqNum);

    CustomPacket *newPacket = new CustomPacket(name);
    newPacket->SetDestination(destinationId);
    newPacket->SetDestinationService(destinationService);
    newPacket->SetSource(ID);
    newPacket->SetSeqNum(seqNum++);
    newPacket->SetType(type);
    newPacket->SetMaxHopCount(maxHopCount);
    newPacket->SetHopCount(0);
    newPacket->SetOriginSourceId(0);
    newPacket->SetProxy(0);

    return newPacket;
}
void PortableDevice::Query(CustomPacket *packet){
    int sourceId = packet->GetSource();
    int maxHopCount = packet->GetMaxHopCount();
    int targetId = ID;
    int originSourceId = packet->GetOriginSourceId();
    int destination = originSourceId == 0 ? sourceId: originSourceId;

    if(Service == packet->GetDestinationService()/* || (targetId = nodeTable.FindService(packet->GetDestinationService())) != -1*/)
    {
        // This node has a target service.
        CustomPacket *reply = GeneratePacket("reply", destination, 0, REPLY, packet->GetHopCount());
        stringstream out;

        out << targetId << "," << packet->GetDestinationService() << "|"; //To reach destination service, Source should send packet to this node.
        reply->SetLastHop(out.str());
        reply->setKind(2);

        forwardMessage(reply);
        delete packet;
    } //limit hop
    else if(maxHopCount <= 0)
    {
        CustomPacket *notice = GeneratePacket("notice", destination, packet->GetDestinationService(), NOTICE, packet->GetHopCount());
        stringstream out;

        out << ID << "," << Service << "|";
        notice->SetLastHop(out.str());
        int originSourceSeqNum = packet->GetOriginSourceId() == 0 ? packet->GetSeqNum(): packet->GetOriginSourceSeqNum();
        notice->SetOriginSourceSeqNum(originSourceSeqNum);
        notice->setKind(2);


        forwardMessage(notice);
        delete packet;
    }
    else if((targetId = nodeTable.FindService(packet->GetDestinationService())) != -1 )
    {
        EV << "yys unicast" << endl;
        stringstream out;
        out << packet->GetLastHop() << ID << "," << Service << "|";
        packet->SetLastHop(out.str());


        packet->SetDestination(targetId);
        packet->SetMaxHopCount(packet->GetMaxHopCount() + 1);
        forwardMessage(packet);
    }
    else
    {
        EV << "yys broadcast" << endl;
        stringstream out;
        out << packet->GetLastHop() << ID << "," << Service << "|";
        packet->SetLastHop(out.str());

        forwardMessage(packet);
    }

}


void PortableDevice::forwardMessage(CustomPacket *packet)
{
    MACAddress destMACAddress;

    int dest = packet->GetDestination();
    //Boradcast
    if(dest == BROADCAST)
    {
        destMACAddress.setBroadcast();
    }
    else
    {
        //find and set macaddress
        string nextHop = routingTable.FindPath(dest);

        if(nextHop.length() == 0)
            destMACAddress.setBroadcast();
        else
            destMACAddress.setAddress(nextHop.c_str());
    }
    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
    etherctrl->setDest(destMACAddress);
    etherctrl->setSrc(MacAddress);

    //*
    if(destMACAddress.isBroadcast())
    {
        //*
        packet->removeControlInfo();
        packet->setControlInfo(etherctrl);

        emit(sentPkSignal, packet);
        sendDelayed(packet, uniform(0, 0.5),"out");
    }
    else
    {
        packet->removeControlInfo();
        packet->setControlInfo(etherctrl);

        emit(sentPkSignal, packet);
        send(packet, "out");
    }
    //*/

}
void PortableDevice::UpdateDisplay()
{
    char buf[40];
    sprintf(buf, "My Service: %d, Current State: %d", Service, currentState);
    getDisplayString().setTagArg("t",0,buf);
}
