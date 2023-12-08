package.path="./?.lua;"..package.path;

local engine=require "engine";
local object=require "gameobject";
local item=require "item";


testname="hahahahahahahahahahahahahahahahahah";

function init(itemId,objectId)
    print("init");
    item.init(itemId);
    object.init(objectId);

end

function tick()

    if(readKeyState("w") or readKeyState("s") or readKeyState("a") or readKeyState("d")) then

        if(readKeyState("w")) then 
            setObjectState(object.Id,"nowState","Up");
            print("tick--w");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",2,1);
            --setObjectState(object.Id,"posY",getObjectState(object.Id,"posY")-5);
        end
        if(readKeyState("s")) then 
 
            setObjectState(object.Id,"nowState","Down");
            print("tick--s");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",4,1);
            --setObjectState(object.Id,"posY",getObjectState(object.Id,"posY")+5);
     
        end
        if(readKeyState("a")) then 

            setObjectState(object.Id,"nowState","Left");
            print("tick--a");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",3,1);
            --setObjectState(object.Id,"posX",getObjectState(object.Id,"posX")-5);

        end
        if(readKeyState("d")) then 
            setObjectState(object.Id,"nowState","Right");
            print("tick--d");
            soluteInstruction(object.Id,"heroMoveToNextElement","Demo",1,1);
            --setObjectState(object.Id,"posX",getObjectState(object.Id,"posX")+5);
        end
    
    else

    setObjectState(object.Id,"nowState","Normal"); 

    end

end
