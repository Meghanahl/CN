#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SecondScriptExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  uint32_t nCsma = 3;

  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc,argv);

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

  nCsma = nCsma == 0 ? 1 : nCsma;

  NodeContainer p2pNodes;
  p2pNodes.Create (2);

  NodeContainer csmaNodes;
  csmaNodes.Add (p2pNodes.Get (1));
  csmaNodes.Create (nCsma);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);

  InternetStackHelper stack;
  stack.Install (p2pNodes.Get (0));
  stack.Install (csmaNodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (p2pNodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  pointToPoint.EnablePcapAll ("second");
  csma.EnablePcap ("second", csmaDevices.Get (1), true);

  AnimationInterface anim("megha.xml");
  anim.SetConstantPosition(p2pNodes.Get(0),47.0,2.0);
  anim.SetConstantPosition(p2pNodes.Get(1),47.0,15.0);
  anim.SetConstantPosition(csmaNodes.Get(1),20.0,45.0);
  anim.SetConstantPosition(csmaNodes.Get(2),50.0,45.0);
  anim.SetConstantPosition(csmaNodes.Get(3),90.0,45.0);
  anim.EnablePacketMetadata(true);
  



  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
/*---output----------------------
bmsce@bmsce-Precision-T1700:~$ cd /home/bmsce/ns-allinone-3.29/ns-3.29
bmsce@bmsce-Precision-T1700:~/ns-allinone-3.29/ns-3.29$ ./waf
Waf: Entering directory `/home/bmsce/ns-allinone-3.29/ns-3.29/build'
Waf: Leaving directory `/home/bmsce/ns-allinone-3.29/ns-3.29/build'
Build commands will be stored in build/compile_commands.json
'build' finished successfully (3.341s)

Modules built:
antenna                   aodv                      applications              
bridge                    buildings                 config-store              
core                      csma                      csma-layout               
dsdv                      dsr                       energy                    
fd-net-device             flow-monitor              internet                  
internet-apps             lr-wpan                   lte                       
mesh                      mobility                  mpi                       
netanim (no Python)       network                   nix-vector-routing        
olsr                      point-to-point            point-to-point-layout     
propagation               sixlowpan                 spectrum                  
stats                     tap-bridge                test (no Python)          
topology-read             traffic-control           uan                       
virtual-net-device        wave                      wifi                      
wimax                     

Modules not built (see ns-3 tutorial for explanation):
brite                     click                     openflow                  
visualizer                

bmsce@bmsce-Precision-T1700:~/ns-allinone-3.29/ns-3.29$ ./waf --run scratch/netanim
Waf: Entering directory `/home/bmsce/ns-allinone-3.29/ns-3.29/build'
Waf: Leaving directory `/home/bmsce/ns-allinone-3.29/ns-3.29/build'
Build commands will be stored in build/compile_commands.json
'build' finished successfully (2.609s)
AnimationInterface WARNING:Node:0 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:1 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:2 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:3 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:4 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:0 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:1 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:2 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:3 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:4 Does not have a mobility model. Use SetConstantPosition if it is stationary
At time 2s client sent 1024 bytes to 10.1.2.4 port 9
At time 2.0078s server received 1024 bytes from 10.1.1.1 port 49153
At time 2.0078s server sent 1024 bytes to 10.1.1.1 port 49153
At time 2.01761s client received 1024 bytes from 10.1.2.4 port 9
bmsce@bmsce-Precision-T1700:~/ns-allinone-3.29/ns-3.29$ cd ..
bmsce@bmsce-Precision-T1700:~/ns-allinone-3.29$ cd netanim-3.108/
bmsce@bmsce-Precision-T1700:~/ns-allinone-3.29/netanim-3.108$ ./NetAnim
Gtk-Message: 12:10:02.715: Failed to load module "canberra-gtk-module"





