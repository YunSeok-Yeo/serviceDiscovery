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

// Created: 2015-2-3 for project servicediscovery

package servicediscovery;

import inet.world.radio.ChannelControl;


//
// A generated network with grid topology.
//
network BottleNeck5
{
    parameters:
        int APs = 0;
        int columns = default(10);
        int rows = default(10);
    submodules:
        WirelessNode0: WirelessNode { @display("p=50,150"); }
        WirelessNode1: WirelessNode { @display("p=350,150"); }
        WirelessNode2: WirelessNode { @display("p=650,150"); }
        WirelessNode3: WirelessNode { @display("p=950,150"); }
        WirelessNode4: WirelessNode { @display("p=1250,150"); }
        WirelessNode5: WirelessNode { @display("p=1550,150"); }
        WirelessNode6: WirelessNode { @display("p=1850,150"); }
        
        WirelessNode7: WirelessNode { @display("p=150,50"); }
        WirelessNode8: WirelessNode { @display("p=250,50"); }
        WirelessNode9: WirelessNode { @display("p=450,50"); }
        WirelessNode10: WirelessNode { @display("p=550,50"); }
        WirelessNode11: WirelessNode { @display("p=750,50"); }
        WirelessNode12: WirelessNode { @display("p=850,50"); }
        WirelessNode13: WirelessNode { @display("p=1050,50"); }
        WirelessNode14: WirelessNode { @display("p=1150,50"); }
        WirelessNode15: WirelessNode { @display("p=1350,50"); }
        WirelessNode16: WirelessNode { @display("p=1450,50"); }
        WirelessNode17: WirelessNode { @display("p=1650,50"); }
        WirelessNode18: WirelessNode { @display("p=1750,50"); }
        
        WirelessNode19: WirelessNode { @display("p=150,250"); }
        WirelessNode20: WirelessNode { @display("p=250,250"); }
        WirelessNode21: WirelessNode { @display("p=450,250"); }
        WirelessNode22: WirelessNode { @display("p=550,250"); }
        WirelessNode23: WirelessNode { @display("p=750,250"); }
        WirelessNode24: WirelessNode { @display("p=850,250"); }
        WirelessNode25: WirelessNode { @display("p=1050,250"); }
        WirelessNode26: WirelessNode { @display("p=1150,250"); }
        WirelessNode27: WirelessNode { @display("p=1350,250"); }
        WirelessNode28: WirelessNode { @display("p=1450,250"); }
        WirelessNode29: WirelessNode { @display("p=1650,250"); }
        WirelessNode30: WirelessNode { @display("p=1750,250"); }
                
        
        channelControl: ChannelControl {
            parameters:
                @display("p=61,46");
        }
    connections allowunconnected:
}
