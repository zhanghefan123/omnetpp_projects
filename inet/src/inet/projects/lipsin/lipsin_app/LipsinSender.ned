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

package inet.projects.lipsin.lipsin_app;

simple LipsinSender{
	parameters:
	    double startTime = default(0);
	    double stopTime = default(-1);
	    double sendInterval = default(1);
	    xml destinationSatellites = default(xml("<LinksConfig></LinksConfig>"));
	  
	    // bloom filter settings
	    int bloomFilterSize = default(40);
	    int numberOfHashFunctions = default(5);
	    
	    // set transmission pattern
	    string transmissionPattern = default("MULTICAST");
	    string multicastPattern = default("PRIMARY");
	    
	    // the packet length
	    int packetLength = default(1000);
	    
        // should enable optimal encoding
        bool enableOptimalEncoding = default(false);
	   
	 gates:
	    input appIn;
	    output appOut;
}