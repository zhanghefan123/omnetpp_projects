package inet.projects.sr.sr_node;

import inet.node.inet.Router;
import inet.projects.sr.sr_app.SRReceiver;
import inet.projects.sr.sr_app.SRSender;
import inet.projects.lipsin.lipsin_table.LipsinLinkTable;
import inet.projects.lipsin.lipsin_table.LipsinRoutingTable;
import inet.projects.lipsin.lipsin_table.LinkInfoTable;
import inet.projects.sr.sr_config_loader.SRConfigLoader;

module SRRouter extends Router
{
    parameters:
        bool hasSRSender = default(false);
        bool hasSRReceiver = default(false);
        xml srConfig = default(xml("<LinksConfig></LinksConfig>"));
        hasSR = true;
    submodules:
        srSender: SRSender if hasSRSender {

        }
        srReceiver: SRReceiver if hasSRReceiver {

        }
        plt: LipsinLinkTable {
             @display("i=block/table;is=s;p=63,31");
        }
        linkInfoTable: LinkInfoTable {
            @display("i=block/table;is=s;p=1471.77,74.95125");
        }
        lipsinRoutingTable: LipsinRoutingTable {
            @display("i=block/table;p=1471.77,374.75626;is=s");
        }
        srConfigLoader: SRConfigLoader {

        }
    connections:
         srSender.appOut --> tn.in++ if hasSRSender;
         srSender.appIn <-- tn.out++ if hasSRSender;

         srReceiver.appOut --> tn.in++ if hasSRReceiver;
         srReceiver.appIn <-- tn.out++ if hasSRReceiver;
}