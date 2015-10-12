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
network BottleNeck1
{
    parameters:
        int APs = 0;
        int columns = default(10);
        int rows = default(10);
    submodules:
        WirelessNode0: WirelessNode { @display("p=50,150"); }
        WirelessNode1: WirelessNode { @display("p=350,150"); }
        WirelessNode2: WirelessNode { @display("p=650,150"); }
        
        WirelessNode3: WirelessNode { @display("p=150,50"); }
        WirelessNode4: WirelessNode { @display("p=250,50"); }
        WirelessNode5: WirelessNode { @display("p=450,50"); }
        WirelessNode6: WirelessNode { @display("p=550,50"); }
                
        WirelessNode7: WirelessNode { @display("p=150,250"); }
        WirelessNode8: WirelessNode { @display("p=250,250"); }
        WirelessNode9: WirelessNode { @display("p=450,250"); }
        WirelessNode10: WirelessNode { @display("p=550,250"); }
                
        
        channelControl: ChannelControl {
            parameters:
                @display("p=61,46");
        }
    connections allowunconnected:
}
