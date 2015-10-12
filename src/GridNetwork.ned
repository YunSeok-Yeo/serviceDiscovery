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
network GridNetwork
{
    parameters:
        int APs = 0;
        int columns = default(10);
        int rows = default(10);
    submodules:
        WirelessNode0: WirelessNode { @display("p=50,50"); }
        WirelessNode1: WirelessNode { @display("p=150,50"); }
        WirelessNode2: WirelessNode { @display("p=250,50"); }
        WirelessNode3: WirelessNode { @display("p=350,50"); }
        WirelessNode4: WirelessNode { @display("p=450,50"); }
        WirelessNode5: WirelessNode { @display("p=550,50"); }
        WirelessNode6: WirelessNode { @display("p=650,50"); }
        WirelessNode7: WirelessNode { @display("p=750,50"); }
        WirelessNode8: WirelessNode { @display("p=850,50"); }
        WirelessNode9: WirelessNode { @display("p=950,50"); }
        WirelessNode10: WirelessNode { @display("p=1050,50"); }
        
        WirelessNode11: WirelessNode { @display("p=50,150"); }
        WirelessNode12: WirelessNode { @display("p=150,150"); }
        WirelessNode13: WirelessNode { @display("p=250,150"); }
        WirelessNode14: WirelessNode { @display("p=350,150"); }
        WirelessNode15: WirelessNode { @display("p=450,150"); }
        WirelessNode16: WirelessNode { @display("p=550,150"); }
        WirelessNode17: WirelessNode { @display("p=650,150"); }
        WirelessNode18: WirelessNode { @display("p=750,150"); }
        WirelessNode19: WirelessNode { @display("p=850,150"); }
        WirelessNode20: WirelessNode { @display("p=950,150"); }
        WirelessNode21: WirelessNode { @display("p=1050,150"); }
        
        WirelessNode22: WirelessNode { @display("p=50,250"); }
        WirelessNode23: WirelessNode { @display("p=150,250"); }
        WirelessNode24: WirelessNode { @display("p=250,250"); }
        WirelessNode25: WirelessNode { @display("p=350,250"); }
        WirelessNode26: WirelessNode { @display("p=450,250"); }
        WirelessNode27: WirelessNode { @display("p=550,250"); }
        WirelessNode28: WirelessNode { @display("p=650,250"); }
        WirelessNode29: WirelessNode { @display("p=750,250"); }
        WirelessNode30: WirelessNode { @display("p=850,250"); }
        WirelessNode31: WirelessNode { @display("p=950,250"); }
        WirelessNode32: WirelessNode { @display("p=1050,250"); }
        
        WirelessNode33: WirelessNode { @display("p=50,350"); }
        WirelessNode34: WirelessNode { @display("p=150,350"); }
        WirelessNode35: WirelessNode { @display("p=250,350"); }
        WirelessNode36: WirelessNode { @display("p=350,350"); }
        WirelessNode37: WirelessNode { @display("p=450,350"); }
        WirelessNode38: WirelessNode { @display("p=550,350"); }
        WirelessNode39: WirelessNode { @display("p=650,350"); }
        WirelessNode40: WirelessNode { @display("p=750,350"); }
        WirelessNode41: WirelessNode { @display("p=850,350"); }
        WirelessNode42: WirelessNode { @display("p=950,350"); }
        WirelessNode43: WirelessNode { @display("p=1050,350"); }
        
        WirelessNode44: WirelessNode { @display("p=50,450"); }
        WirelessNode45: WirelessNode { @display("p=150,450"); }
        WirelessNode46: WirelessNode { @display("p=250,450"); }
        WirelessNode47: WirelessNode { @display("p=350,450"); }
        WirelessNode48: WirelessNode { @display("p=450,450"); }
        WirelessNode49: WirelessNode { @display("p=550,450"); }
        WirelessNode50: WirelessNode { @display("p=650,450"); }
        WirelessNode51: WirelessNode { @display("p=750,450"); }
        WirelessNode52: WirelessNode { @display("p=850,450"); }
        WirelessNode53: WirelessNode { @display("p=950,450"); }
        WirelessNode54: WirelessNode { @display("p=1050,450"); }
        
        WirelessNode55: WirelessNode { @display("p=50,550"); }
        WirelessNode56: WirelessNode { @display("p=150,550"); }
        WirelessNode57: WirelessNode { @display("p=250,550"); }
        WirelessNode58: WirelessNode { @display("p=350,550"); }
        WirelessNode59: WirelessNode { @display("p=450,550"); }
        WirelessNode60: WirelessNode { @display("p=550,550"); }
        WirelessNode61: WirelessNode { @display("p=650,550"); }
        WirelessNode62: WirelessNode { @display("p=750,550"); }
        WirelessNode63: WirelessNode { @display("p=850,550"); }
        WirelessNode64: WirelessNode { @display("p=950,550"); }
        WirelessNode65: WirelessNode { @display("p=1050,550"); }
        
        WirelessNode66: WirelessNode { @display("p=50,650"); }
        WirelessNode67: WirelessNode { @display("p=150,650"); }
        WirelessNode68: WirelessNode { @display("p=250,650"); }
        WirelessNode69: WirelessNode { @display("p=350,650"); }
        WirelessNode70: WirelessNode { @display("p=450,650"); }
        WirelessNode71: WirelessNode { @display("p=550,650"); }
        WirelessNode72: WirelessNode { @display("p=650,650"); }
        WirelessNode73: WirelessNode { @display("p=750,650"); }
        WirelessNode74: WirelessNode { @display("p=850,650"); }
        WirelessNode75: WirelessNode { @display("p=950,650"); }
        WirelessNode76: WirelessNode { @display("p=1050,650"); }
        
        WirelessNode77: WirelessNode { @display("p=50,750"); }
        WirelessNode78: WirelessNode { @display("p=150,750"); }
        WirelessNode79: WirelessNode { @display("p=250,750"); }
        WirelessNode80: WirelessNode { @display("p=350,750"); }
        WirelessNode81: WirelessNode { @display("p=450,750"); }
        WirelessNode82: WirelessNode { @display("p=550,750"); }
        WirelessNode83: WirelessNode { @display("p=650,750"); }
        WirelessNode84: WirelessNode { @display("p=750,750"); }
        WirelessNode85: WirelessNode { @display("p=850,750"); }
        WirelessNode86: WirelessNode { @display("p=950,750"); }
        WirelessNode87: WirelessNode { @display("p=1050,750"); }
        
        WirelessNode88: WirelessNode { @display("p=50,850"); }
        WirelessNode89: WirelessNode { @display("p=150,850"); }
        WirelessNode90: WirelessNode { @display("p=250,850"); }
        WirelessNode91: WirelessNode { @display("p=350,850"); }
        WirelessNode92: WirelessNode { @display("p=450,850"); }
        WirelessNode93: WirelessNode { @display("p=550,850"); }
        WirelessNode94: WirelessNode { @display("p=650,850"); }
        WirelessNode95: WirelessNode { @display("p=750,850"); }
        WirelessNode96: WirelessNode { @display("p=850,850"); }
        WirelessNode97: WirelessNode { @display("p=950,850"); }
        WirelessNode98: WirelessNode { @display("p=1050,850"); }
        
        WirelessNode99: WirelessNode { @display("p=50,950"); }
        WirelessNode100: WirelessNode { @display("p=150,950"); }
        WirelessNode101: WirelessNode { @display("p=250,950"); }
        WirelessNode102: WirelessNode { @display("p=350,950"); }
        WirelessNode103: WirelessNode { @display("p=450,950"); }
        WirelessNode104: WirelessNode { @display("p=550,950"); }
        WirelessNode105: WirelessNode { @display("p=650,950"); }
        WirelessNode106: WirelessNode { @display("p=750,950"); }
        WirelessNode107: WirelessNode { @display("p=850,950"); }
        WirelessNode108: WirelessNode { @display("p=950,950"); }
        WirelessNode109: WirelessNode { @display("p=1050,950"); }
        
        WirelessNode110: WirelessNode { @display("p=50,1050"); }
        WirelessNode111: WirelessNode { @display("p=150,1050"); }
        WirelessNode112: WirelessNode { @display("p=250,1050"); }
        WirelessNode113: WirelessNode { @display("p=350,1050"); }
        WirelessNode114: WirelessNode { @display("p=450,1050"); }
        WirelessNode115: WirelessNode { @display("p=550,1050"); }
        WirelessNode116: WirelessNode { @display("p=650,1050"); }
        WirelessNode117: WirelessNode { @display("p=750,1050"); }
        WirelessNode118: WirelessNode { @display("p=850,1050"); }
        WirelessNode119: WirelessNode { @display("p=950,1050"); }
        WirelessNode120: WirelessNode { @display("p=1050,1050"); }
        
        channelControl: ChannelControl {
            parameters:
                @display("p=61,46");
        }
    connections allowunconnected:
}
