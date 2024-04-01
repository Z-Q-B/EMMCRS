#include <veins/modules/application/traci/MyVeinsApp.h>

using namespace veins;

Define_Module(veins::MyVeinsApp);

double MyVeinsApp::totalDelay = 0;
long MyVeinsApp::totalPacketsReceived = 0;

void MyVeinsApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);

    if (stage == 0) {
        sendBeacon = new cMessage("send Beacon");
        // Initializing members and pointers of your application goes here
        EV << "Initializing " << std::endl;
    }
    else if (stage == 1) {
        if (sendBeacon->isScheduled()) {
                     cancelEvent(sendBeacon);
              }
              scheduleAt(simTime()+5,sendBeacon);
           }

}

void MyVeinsApp::finish()
{


    DemoBaseApplLayer::finish();

    simtime_t time4=totalDelay;
 
    EV << "time:"<<time4/totalPacketsReceived*1000<< std::endl;

    // statistics recording goes here
}

void MyVeinsApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
}

void MyVeinsApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsApp::handleSelfMsg(cMessage* msg)
{
    if (msg == sendBeacon) {
        Beacon* beacon = new Beacon();
        beacon->setTime(simTime());

        //Set length based on scheme message size
        beacon->setByteLength(Message length);

        BaseFrame1609_4* WSM = new BaseFrame1609_4();
         
                  WSM->encapsulate(beacon);
                  populateWSM(WSM);
                  WSM->setByteLength( beacon->getByteLength());
                  sendDown(WSM); 

                  scheduleAt(simTime()+5,sendBeacon);
                  return;
    }
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission
}

void MyVeinsApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
}

void MyVeinsApp::handleLowerMsg(cMessage* msg) {
     messageQueue.push(msg);
        if (messageQueue.size() != 0) {
            processMessageQueue();
        }
 }

void MyVeinsApp::processMessageQueue() {

    while (!messageQueue.empty()) {
        cMessage* msg = messageQueue.front();
        messageQueue.pop();

       BaseFrame1609_4* WSM = check_and_cast<BaseFrame1609_4*>(msg);

            cPacket* enc = WSM->getEncapsulatedPacket();
                    Beacon* bc = check_and_cast<Beacon*>(enc);
                    simtime_t time1=bc->getTime();
                    simtime_t time2=simTime();
                    simtime_t time3=time2-time1;

                    totalPacketsReceived++;
                    totalDelay += time3.dbl();
                    simtime_t time4=totalDelay;
                    delete msg; 
    }
}