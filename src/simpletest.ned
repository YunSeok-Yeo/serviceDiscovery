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

package servicediscovery;

//
// TODO auto-generated type
//

import inet.world.radio.ChannelControl;


channel Link extends ned.DatarateChannel
{
    parameters:
        int cost = default(0);
        @display("ls=red,,d");
}

channel WiredLink extends ned.DatarateChannel
{
    parameters:
        int cost = default(0);
}
network Simpletest
{
    parameters:
        int APs = 1;
        int cliNum = default(10);
    submodules:
        Server: Server_DNS {
            @display("p=0,0");
        }
        AP1: AP {
            @display("p=750,750");
        }
        WirelessNode[cliNum]: WirelessNode{
        }
        channelControl: ChannelControl {
            parameters:
                @display("p=61,46");
        }
    connections:

        Server.g++ <--> WiredLink <--> AP1.g;
}
