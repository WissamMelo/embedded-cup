#ifndef PAYLOADENCODER_H_
#define PAYLOADENCODER_H_

namespace smc {
    typedef struct moment {
        unsigned int hour;
        unsigned int minute;
        unsigned int day;
        unsigned int month;
        unsigned int year;
    } Moment;

    typedef struct hourMinute {
        unsigned int hour;	
        unsigned int minute;
    } HourMinute;

    typedef struct alarmInfo {
        hourMinute start;
        hourMinute period;
        unsigned int duration;
    } AlarmInfo;

    class PayloadEncoder {
        public:
            unsigned int idCup;
            unsigned int partition;
            Moment moment;
            String event;
            AlarmInfo alarmInfo;

            PayloadEncoder(){}

            PayloadEncoder(unsigned int idCup, unsigned int partition, Moment moment, String event, AlarmInfo alarmInfo){
                this->idCup = idCup;
                this->partition = partition;
                this->moment = moment;
                this->event = event;
                this->alarmInfo = alarmInfo;
            }

            ~PayloadEncoder(){}

            String encode(){
                String payload = "";

                if(isEventValid(event)) {
                    String alarmInfoStr = "{}";
                    if(event == "registered") {
                        alarmInfoStr = encodeAlarmInfo(alarmInfo);
                    }

                    String momentStr = encodeMoment(moment);

                    char buffer[1000];
                    sprintf(
                            buffer,
                            "{"
                            "\"id_cup\": %u, "
                            "\"partition\": %u, "
                            "\"moment\": \"%s\", "
                            "\"event\": \"%s\", "
                            "\"alarm_info\": %s"
                            "}",
                            idCup, partition, momentStr.c_str(), event.c_str(), alarmInfoStr.c_str()
                           );
                    payload = String(buffer);
                } else {
                    Serial.println("[ERROR] Invalid event!");
                }

                return payload;
            }

        private:
            String encodeAlarmInfo(AlarmInfo alarmInfo) {
                String startStrAux = encodeHourMinute(alarmInfo.start);
                String periodStrAux = encodeHourMinute(alarmInfo.period);

                String alarmInfoStr = "";
                if(alarmInfo.start.hour <= 23 and alarmInfo.start.minute <= 59 and
                        alarmInfo.period.hour <= 23 and alarmInfo.period.minute <= 59){
                    char buffer[1000];
                    sprintf(buffer, "{\"start\": %s, \"period\": %s, \"duration\": %u}", startStrAux.c_str(), periodStrAux.c_str(), alarmInfo.duration);
                    alarmInfoStr = String(buffer);
                } else {
                    Serial.println("[ERROR] Invalid alarmInfo attribute value, wrong range.");	
                }

                return alarmInfoStr;
            }

            String encodeMoment(Moment moment) {
                String momentStr = "";

                if(moment.hour <= 23 and moment.minute <= 59 and moment.day <= 31 and 
                        moment.month <= 12 and moment.year >= 2018 and moment.year <= 2050){
                    char buffer[1000];
                    sprintf(buffer, "%u-%u-%u %u:%u", moment.year, moment.month, moment.day, moment.hour, moment.minute);	
                    momentStr = String(buffer);
                } else {
                    Serial.println("[ERROR] Invalid moment attribute value, wrong range.");	
                }

                return momentStr;
            }

            String encodeHourMinute(HourMinute hourTime){
                String hourMinuteStr = "";

                if(hourTime.hour <= 23 and hourTime.minute <= 59) {
                    char buffer[1000];
                    sprintf(buffer, "{\"hour\": %u, \"minute\": %u}", hourTime.hour, hourTime.minute);
                    hourMinuteStr = String(buffer);
                } else {
                    Serial.println("[ERROR] Invalid hourTime attribute value for encoding hourTime.");	
                }

                return hourMinuteStr;
            }

            bool isEventValid(String event){
                const String possibleEvents[] = {"taken", "not_taken", "registered", "removed"};
                const int possibleEventsLen = 4;

                for(int i = 0; i < possibleEventsLen; ++i){
                    if(event == possibleEvents[i]) {
                        return true;
                    }
                }
                return false;
            }
    };
}

#endif  // PAYLOADENCODER_H_
