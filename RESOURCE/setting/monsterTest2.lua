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

timerState=0;
timerIndex=0;
timerIndexMax=15;


function tick()

    timerIndex=timerIndex+1;
    if(timerIndex>=timerIndexMax) then
        timerIndex=0;
        timerState=timerState+1;
        if(timerState>2) then
            timerState=0;
        end
    end

    if(timerState==0) then
        setObjectState(object.Id,"nowState","Left");
        soluteInstruction(object.Id,"monsterMoveToNextElement","Demo",3,1);
    else if(timerState==1) then
        setObjectState(object.Id,"nowState","Right");
        soluteInstruction(object.Id,"monsterMoveToNextElement","Demo",1,1);
    else if(timerState==2)  then
        setObjectState(object.Id,"nowState","Normal"); 
    end

end
