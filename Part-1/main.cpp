/* need to run shell command */
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include <uWS/uWS.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include <stdlib.h>
#include <stdio.h>

#include <thread>

#include <boost/regex.hpp>                // regex for string parsing

std::stringstream indexHtml;

uWS::Hub h;

std::vector<std::string> storedMessages;
std::vector<int> excludedMessages;

void uws(void) {

    indexHtml << std::ifstream ("index.html").rdbuf();
    if (!indexHtml.str().length()) {
        std::cerr << "Failed to load index.html" << std::endl;
        return -1;
    }

    // hello world :) 
    storedMessages.push_back("234,96,234,96,234,102,234,110,234,128,234,138,234,156,236,172,238,188,240,208,242,220,244,234,246,246,246,256,248,262,248,266,248,270,248,272,248,274,248,276,248,278 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("252,196,252,196,254,196,258,196,266,196,276,196,286,196,294,196,304,196,312,196,318,196,320,196,322,196,324,196 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("326,112,326,112,326,114,326,118,326,128,326,140,326,150,326,158,326,164,326,172,326,184,326,196,326,208,328,228,330,236,330,244,332,248,332,250,332,254,332,256 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("392,232,392,232,398,232,402,232,408,232,412,232,414,232,418,232,422,232,426,232,430,226,430,222,432,218,434,216,434,214,434,212,430,208,426,204,420,198,416,194,414,194,410,192,408,192,406,192,402,192,402,194,398,196,398,198,396,200,396,202,396,204,396,206,396,210,396,214,396,226,396,230,396,236,396,240,396,242,396,246,396,250,396,252,398,254,400,256,400,258,402,260,408,260,412,260,414,260,416,260,418,260,420,260,424,260,426,260,428,260,430,260,432,260,434,260,436,260 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("478,126,478,126,478,132,478,134,478,148,478,152,478,162,478,172,478,180,478,192,478,204,478,222,478,234,478,242,478,246,478,252,478,254,478,256,478,258 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("510,138,510,138,510,140,510,144,510,156,510,170,510,182,510,194,510,204,510,212,510,226,510,234,510,240,510,244,510,248,510,250,510,252 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("572,234,572,234,570,234,566,234,564,234,556,234,552,234,550,236,550,238,550,240,550,242,550,244,550,248,550,254,552,256,554,262,556,266,558,268,562,272,564,274,566,276,568,278,570,278,572,278,576,276,580,274,580,272,584,270,584,266,586,264,588,260,588,258,588,256,588,254,586,250,584,248,584,246,584,244,582,244,582,242,582,240,580,240,580,238 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("368,336,368,336,368,340,368,356,368,372,370,382,372,396,372,404,374,410,376,414,380,416,382,418,386,422,390,424,396,424,398,424,402,418,404,412,406,402,408,396,408,392,408,388,408,390,410,392,412,394,414,396,416,400,418,400,422,402,424,404,426,406,430,406,432,408,436,408,440,408,444,408,444,406,446,406,448,404,448,400,450,396,452,394,452,390,452,388,452,386,452,384,452,380,452,378,454,372,454,364,454,358,454,350,454,348 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("502,392,502,392,498,394,494,398,490,400,488,402,488,404,488,408,488,410,488,412,488,416,488,418,488,422,488,428,490,432,494,438,496,440,498,442,500,442,502,442,504,442,506,440,508,438,512,436,514,434,516,430,518,426,520,420,520,414,520,408,520,406,520,404,520,402,518,402,514,398,510,398,508,396,508,394,506,394,506,392,506,388 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("558,442,558,442,558,440,558,438,558,432,558,428,558,420,558,414,558,410,558,406,558,404,558,402,558,400,560,400,560,398,562,398,566,398,568,396,574,396,574,394,578,394,580,394,582,394,584,394 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("622,348,622,348,622,350,622,354,622,366,622,370,622,378,622,388,622,394,622,400,622,406,622,414,622,418,622,422,622,424,622,428,622,430,622,434,622,438,622,440,622,442 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("702,344,702,344,702,346,702,350,702,356,702,364,702,374,702,384,702,392,702,400,702,408,702,410,702,416,702,418,702,420,702,424,702,426,702,428,700,430,694,432,688,436,680,436,678,436,674,436,672,436,670,436,668,434,666,434,666,432,664,430,662,424,662,420,660,418,660,416,660,414,660,412,662,410,662,408,666,406,668,406,670,404,674,404,676,402,678,402,682,402,684,402,686,402,688,402,690,402,692,402,694,402,696,402 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("218,706,218,706,218,704,218,700,218,696,218,688,218,682,218,674,218,666,218,646,220,634,224,622,228,614,234,604,240,594,242,590,250,580,256,576,262,570,274,562,286,556,298,550,316,546,328,540,340,536,350,534,360,532,370,528,380,526,390,522,400,520,416,518,430,518,438,518,448,518,458,520,470,522,482,526,492,532,502,538,512,542,524,548,538,560,542,566,550,574,554,580,560,586,564,592,566,600,570,608,574,614,578,622,582,628,586,638,590,644,592,650,596,658,600,662,602,668,604,674,606,676,608,684,612,692,614,698,616,700,616,704,616,706,616,708 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("304,604,304,604 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("500,602,500,602 {\"r\":0,\"g\":0,\"b\":0}"); storedMessages.push_back("366,636,366,636,366,640,366,642,366,644,366,646,366,648,366,650,368,652,370,656,372,658,374,662,376,662,378,664,380,664,382,664,384,664,386,664,390,664,392,664,394,664,396,664,398,664,400,664,402,664,404,662,406,660,408,658,410,658,410,656,410,654,410,652,410,650,410,648 {\"r\":0,\"g\":0,\"b\":0}");

    h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
      // send index.hmtl regardless of req
      res->end(indexHtml.str().data(), indexHtml.str().length());
    });

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
      // send this client all stored messages in one batch send
      uWS::WebSocket<uWS::SERVER>::PreparedMessage *pMB = uWS::WebSocket<uWS::SERVER>::prepareMessageBatch(storedMessages, excludedMessages, uWS::TEXT, false);
      ws->sendPrepared(pMB);
      ws->finalizeMessage(pMB);
    });

    h.onMessage([&h](uWS::WebSocket<uWS::SERVER> *ws, char *data, size_t length, uWS::OpCode opCode) {
        
      if (length && length < 4096) {
        // check message with regex
        boost::regex rgx{"^[0-9]+,[0-9]+(,[0-9]+,[0-9]+)* \\{\"r\":(0|(0\.[0-9]*)|1),\"g\":(0|(0\.[0-9]*)|1),\"b\":(0|(0\.[0-9]*)|1)\\}$"};
        std::string str(data, length);
        bool match = boost::regex_match(str, rgx);
        if(match) {
          // store message
          if (storedMessages.size() >= 200) {
            storedMessages.erase(storedMessages.begin());
          }
          storedMessages.push_back(str);

          // simply broadcast this message to everyone (completely without any timeout optimization!)
          h.getDefaultGroup<uWS::SERVER>().broadcast(data, length, uWS::TEXT);
        }
      }
    });

    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> *ws, int code, char *message, size_t length) {
    
    });

    h.getDefaultGroup<uWS::SERVER>().startAutoPing(30000);
    // always use 80
    if (h.listen(80)) {
        std::cout << "Listening to port 80" << std::endl;
    } else {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }
    h.run();
}

int main() {
  
    std::thread uwsThread (uws); 

    // synchronize thread(s):
    std::cout << "wait to close" << std::endl;
    uwsThread.join();                // pauses until first finishes

    return 0;
    // kills all threads
    //std::terminate();
}
