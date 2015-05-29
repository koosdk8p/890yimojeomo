package com.springapp.mvc;

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    public static String[] names = {"드온","영균","한결","민승","범준","선아","슬지","기하","지헌","형진","로사","주연","도연","영민","혜원"};
    public static String[] namesfull = {"기드온","황영균","박한결","김민승","김범준","김선아","김슬지","남기하","김지헌","안형진","이로사","이주연","임도연","임영민","정혜원"};
    public static String[] boys = {"기드온","황영균","내오빠♥","김범준","남기하","김지헌","안형진","임영민"};
    public static String[] girls = {"김민승","김선아","김슬지","이로사","회원님","임도연","정혜원","(알수없음)"};
    public static String[] words = {"커플","솔로","대박","하아","헐","배고","치킨","치맥","치느님","맥주","술","소주","생일","선물","라임","여자친구","남자친구","성당"};

    public static Pattern datePattern = Pattern.compile("^\\d{4}년\\s\\d+월\\s\\d+일\\s(오후|오전)\\s\\d+:\\d+,.*");
    public static Pattern namePattern = Pattern.compile("^.*,\\s.*\\s:.*");
    public static Pattern messegePattern = Pattern.compile(".*:\\s.*");
    public static Pattern invitePattern = Pattern.compile(".*님이\\s.*초대했습니다.");

    public static void main(String[] args) throws IOException {


        File file = new File("/Users/duonki/work/personal/890/src/KakaoTalkChats_original.txt");


        HashMap<String,Integer> individualFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> dateFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> hourFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> laughFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> cryFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> photoFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> nameFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> wordFrequency = new HashMap<String,Integer>();
        HashMap<String,Integer> emojiFrequency = new HashMap<String,Integer>();

        TreeMap<String,String> joinDate = new TreeMap<String,String>();

        int groupNumber = 0, boysTalkNum = 0, girlsTalkNum = 0;
        String longestChat = "";

        FileInputStream fis = new FileInputStream(file);

        //Construct BufferedReader from InputStreamReader
        BufferedReader br = new BufferedReader(new InputStreamReader(fis));

        String line = null;
        int lineNum = 0;
        while ((line = br.readLine()) != null) {
            //Checking longest chat
            if(line.length() > longestChat.length() && !line.contains("(") && !line.contains("http")){
                longestChat = line;
            }
            //Checking word frequency
            for(String s:words){
                if(line.contains(s)){
                    if(wordFrequency.containsKey(s)){
                        wordFrequency.put(s,wordFrequency.get(s)+1);
                    }
                    else{
                        wordFrequency.put(s,1);
                    }
                }
            }


            Matcher m = datePattern.matcher(line);
            if(m.matches()){
                //Checking date/hour frequency
                String year = line.split("년")[0];
                String month = line.split("년")[1].split("월")[0].substring(1,line.split("년")[1].split("월")[0].length());
                String day = line.split("년")[1].split("월")[1].split("일")[0].substring(1,line.split("년")[1].split("월")[1].split("일")[0].length());
                String ampm = line.split("년")[1].split("월")[1].split("일")[1]
                        .substring(1,line.split("년")[1].split("월")[1].split("일")[1].length())
                        .split(" ")[0];
                String hour = line.split("년")[1].split("월")[1].split("일")[1]
                        .substring(1,line.split("년")[1].split("월")[1].split("일")[1].length())
                        .split(" ")[1].split(":")[0];

                if(dateFrequency.containsKey(year+"년 "+month+"월 "+day+"일")){
                    dateFrequency.put(year+"년 "+month+"월 "+day+"일",
                            dateFrequency.get(year+"년 "+month+"월 "+day+"일")+1);
                }
                else{
                    dateFrequency.put(year+"년 "+month+"월 "+day+"일",1);
                }

                if(hourFrequency.containsKey(ampm + " " + hour + "시")){
                    hourFrequency.put(ampm+" "+hour+"시",hourFrequency.get(ampm+" "+hour+"시")+1);
                }
                else{
                    hourFrequency.put(ampm+" "+hour+"시",1);
                }

                //  sub - Adding when an individual joined the room
                Matcher inviteMatcher = invitePattern.matcher(line);
                joinDate.put("이주연", "2014년 6월 3일");
                if(inviteMatcher.matches()){
                    String[] lineSplit = line.split(",");
                    if(lineSplit.length == 2){
                        int nameIndex = lineSplit[1].indexOf("을");
                        int spaceIndex = lineSplit[1].indexOf(" ",4);
                        String inviteeName = lineSplit[1].substring(spaceIndex+1,nameIndex-1);
                        if(inviteeName.equals("(알수없음)")){
                            if(!joinDate.containsKey("김선아") && day.equals("9")){
                                joinDate.put("김선아", year + "년 " + month + "월 " + day + "일");
                            }
                            if(!joinDate.containsKey("김민승") && day.equals("31")){
                                joinDate.put("김민승", year + "년 " + month + "월 " + day + "일");
                            }
                        }
                        else if(inviteeName.equals("김선아") || inviteeName.equals("김민승")){

                        }
                        else {
                            joinDate.put(inviteeName, year + "년 " + month + "월 " + day + "일");
                        }
                    }
                    if(lineSplit.length > 2){
                        lineSplit = line.split("님이");
                        lineSplit = lineSplit[1].split(",");
                        for(int i=0; i<lineSplit.length; i++){
                            int nameIndex = lineSplit[i].indexOf("님");
                            int spaceIndex = lineSplit[i].indexOf(" ");
                            String inviteeName = lineSplit[i].substring(spaceIndex + 1, nameIndex);
                            joinDate.put(inviteeName, year + "년 " + month + "월 " + day + "일");
                            if(i == lineSplit.length-1){
                                nameIndex = lineSplit[i].indexOf("님",6);
                                spaceIndex = lineSplit[i].indexOf(" ",2);
                                inviteeName = lineSplit[i].substring(spaceIndex + 1, nameIndex);
                                joinDate.put(inviteeName, year + "년 " + month + "월 " + day + "일");

                            }
                        }
                    }
                }


                //Checking individual talk frequency
                Matcher nameMatcher = namePattern.matcher(line);
                if(nameMatcher.matches()) {
                    String name = line.split(",")[1].substring(1, line.split(",")[1].length()).split(" ")[0];
                    // sub - counting boys/girls talk count
                    for(String s:boys){
                        if(name.equals(s)){
                            boysTalkNum++;
                        }
                    }
                    for(String s:girls){
                        if(name.equals(s)){
                            girlsTalkNum++;
                        }
                    }

                    if ((individualFrequency.containsKey(name) || name.equals("(알수없음)"))) {
                        if(name.equals("(알수없음)") && individualFrequency.containsKey("김선아") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                            individualFrequency.put("김선아",individualFrequency.get("김선아")+1);
                        }
                        else if(name.equals("(알수없음)") && individualFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                            individualFrequency.put("김민승",individualFrequency.get("김민승")+1);
                        }
                        else if(name.equals("(알수없음)") && !individualFrequency.containsKey("김민승") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                            individualFrequency.put("김선아",1);
                        }
                        else if(name.equals("(알수없음)") && !individualFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                            individualFrequency.put("김민승",1);
                        }
                        else {
                            individualFrequency.put(name, individualFrequency.get(name) + 1);
                        }
                    } else {
                        individualFrequency.put(name,1);

                    }
                    //  sub - Checking "ㅋ|" and "ㅠ|ㅜ" frequency
                    if(line.contains("ㅋ") | line.contains("ㅎ")){
                        name = line.split(",")[1].substring(1, line.split(",")[1].length()).split(" ")[0];
                        if ((laughFrequency.containsKey(name) || name.equals("(알수없음)"))) {
                            if(name.equals("(알수없음)") && laughFrequency.containsKey("김선아") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                laughFrequency.put("김선아",laughFrequency.get("김선아")+1);
                            }
                            else if(name.equals("(알수없음)") && laughFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                laughFrequency.put("김민승",laughFrequency.get("김민승")+1);
                            }
                            else if(name.equals("(알수없음)") && !laughFrequency.containsKey("김민승") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                laughFrequency.put("김선아",1);
                            }
                            else if(name.equals("(알수없음)") && !laughFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                laughFrequency.put("김민승",1);
                            }
                            else {
                                laughFrequency.put(name, laughFrequency.get(name) + 1);
                            }
                        } else {
                            laughFrequency.put(name,1);

                        }
                    }
                    if(line.contains("ㅠ") || line.contains("ㅜ")){
                        name = line.split(",")[1].substring(1, line.split(",")[1].length()).split(" ")[0];
                        if ((cryFrequency.containsKey(name) || name.equals("(알수없음)"))) {
                            if(name.equals("(알수없음)") && cryFrequency.containsKey("김선아") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                cryFrequency.put("김선아",cryFrequency.get("김선아")+1);
                            }
                            else if(name.equals("(알수없음)") && cryFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                cryFrequency.put("김민승",cryFrequency.get("김민승")+1);
                            }
                            else if(name.equals("(알수없음)") && !cryFrequency.containsKey("김민승") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                cryFrequency.put("김선아",1);
                            }
                            else if(name.equals("(알수없음)") && !cryFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                cryFrequency.put("김민승",1);
                            }
                            else {
                                cryFrequency.put(name, cryFrequency.get(name) + 1);
                            }
                        } else {
                            cryFrequency.put(name,1);

                        }
                    }
                    //  sub - Checking photo frequency
                    if(line.contains("<사진>")){
                        name = line.split(",")[1].substring(1, line.split(",")[1].length()).split(" ")[0];
                        if ((photoFrequency.containsKey(name) || name.equals("(알수없음)"))) {
                            if(name.equals("(알수없음)") && photoFrequency.containsKey("김선아") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                photoFrequency.put("김선아",photoFrequency.get("김선아")+1);
                            }
                            else if(name.equals("(알수없음)") && photoFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                photoFrequency.put("김민승",photoFrequency.get("김민승")+1);
                            }
                            else if(name.equals("(알수없음)") && !photoFrequency.containsKey("김민승") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                photoFrequency.put("김선아",1);
                            }
                            else if(name.equals("(알수없음)") && !photoFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                photoFrequency.put("김민승",1);
                            }
                            else {
                                photoFrequency.put(name, photoFrequency.get(name) + 1);
                            }
                        } else {
                            photoFrequency.put(name,1);

                        }
                    }
                }

                //  sub - Checking how many times an individual was called
                Matcher calledMatcher = messegePattern.matcher(line);
                if (calledMatcher.matches()) {
                    String name = line.split(",")[1].substring(1, line.split(",")[1].length()).split(" ")[0];
                    String messege = line.split(":")[2];
                    if(messege.contains("(") && messege.contains(")")){
                        if ((emojiFrequency.containsKey(name) || name.equals("(알수없음)"))) {
                            if(name.equals("(알수없음)") && emojiFrequency.containsKey("김선아") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                emojiFrequency.put("김선아",emojiFrequency.get("김선아")+1);
                            }
                            else if(name.equals("(알수없음)") && emojiFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                emojiFrequency.put("김민승",emojiFrequency.get("김민승")+1);
                            }
                            else if(name.equals("(알수없음)") && !emojiFrequency.containsKey("김민승") && Integer.parseInt(year) == 2014 && Integer.parseInt(month) < 9){
                                emojiFrequency.put("김선아",1);
                            }
                            else if(name.equals("(알수없음)") && !emojiFrequency.containsKey("김민승") && (Integer.parseInt(year) == 2014 || Integer.parseInt(year) == 2015) && (Integer.parseInt(month) >= 9 || Integer.parseInt(month) <= 2)){
                                emojiFrequency.put("김민승",1);
                            }
                            else {
                                emojiFrequency.put(name, emojiFrequency.get(name) + 1);
                            }
                        } else {
                            emojiFrequency.put(name,1);
                        }

                    }


                    for(String s : names){
                        if(messege.contains(s)){
                            if (nameFrequency.containsKey(s)) {
                                nameFrequency.put(s, nameFrequency.get(s) + 1);
                            } else {
                                nameFrequency.put(s, 1);
                            }
                        }
                    }

                    // sub sub - Checking for the number of times "890" or "팔구공" has been called
                    if(messege.contains("890") || messege.contains("팔구공")){
                        groupNumber++;
                    }
                }
            }
        }

        br.close();

        System.out.println("날짜별 대화 횟수");

        Map<String,Integer> sortedNum = sortByComparator(dateFrequency);
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()){
            System.out.printf("날짜 : %s   대화 횟수: %s %n", entry.getKey(), entry.getValue());
        }

        System.out.println();
        System.out.println("시간별 대화 횟수");

        sortedNum = sortByComparator(hourFrequency);
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()){
            System.out.printf("날짜 : %s   대화 횟수: %s %n", entry.getKey(), entry.getValue());
        }

        System.out.println();

        sortedNum = sortByComparator(individualFrequency);
        int totalNum = 0;
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            totalNum += entry.getValue();
        }
        System.out.println("개인별 대화 횟수 : 총 " + totalNum + "개");

        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()){
            if(entry.getKey().equals("회원님")){
                System.out.printf("이름 : %s   대화 횟수: %s %n", "이주연", entry.getValue());
            }
            else if(entry.getKey().equals("내오빠♥")){
                System.out.printf("이름 : %s   대화 횟수: %s %n", "박한결", entry.getValue());
            }
            else {
                System.out.printf("이름 : %s   대화 횟수: %s %n", entry.getKey(), entry.getValue());
            }
        }

        System.out.println();

        sortedNum = sortByComparator(laughFrequency);
        totalNum = 0;
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            totalNum += entry.getValue();
        }
        System.out.println("개인별 웃은 횟수 : 총 " + totalNum + "번");

        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()){
            if(entry.getKey().equals("회원님")){
                System.out.printf("이름 : %s   대화 횟수: %s %n", "이주연", entry.getValue());
            }
            else if(entry.getKey().equals("내오빠♥")){
                System.out.printf("이름 : %s   대화 횟수: %s %n", "박한결", entry.getValue());
            }
            else {
                System.out.printf("이름 : %s   대화 횟수: %s %n", entry.getKey(), entry.getValue());
            }
        }

        System.out.println();

        sortedNum = sortByComparator(cryFrequency);
        totalNum = 0;
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            totalNum += entry.getValue();
        }
        System.out.println("개인별 울은 횟수 : 총 " + totalNum + "번");

        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()){
            if(entry.getKey().equals("회원님")){
                System.out.printf("이름 : %s   대화 횟수: %s %n", "이주연", entry.getValue());
            }
            else if(entry.getKey().equals("내오빠♥")){
                System.out.printf("이름 : %s   대화 횟수: %s %n", "박한결", entry.getValue());
            }
            else {
                System.out.printf("이름 : %s   대화 횟수: %s %n", entry.getKey(), entry.getValue());
            }
        }

        System.out.println();

        sortedNum = sortByComparator(photoFrequency);
        totalNum = 0;
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            totalNum += entry.getValue();
        }
        System.out.println("개인별 사진올린 횟수 : 총 " + totalNum + "개");

        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()){
            if(entry.getKey().equals("회원님")){
                System.out.printf("이름 : %s   올린 횟수: %s %n", "이주연", entry.getValue());
            }
            else if(entry.getKey().equals("내오빠♥")){
                System.out.printf("이름 : %s   올린 횟수: %s %n", "박한결", entry.getValue());
            }
            else {
                System.out.printf("이름 : %s   올린 횟수: %s %n", entry.getKey(), entry.getValue());
            }
        }

        System.out.println();

        sortedNum = sortByComparator(nameFrequency);
        totalNum = 0;
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            totalNum += entry.getValue();
        }
        System.out.println("개인별 이름 불린 횟수 : 총 " + totalNum + "번");
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            System.out.printf("이름 : %s   불린 횟수: %s %n", entry.getKey(), entry.getValue());
        }

        System.out.println();
        System.out.println("890 입문 날짜");
        for(Map.Entry<String, String> entry : joinDate.entrySet()) {
            if(entry.getKey().equals("내오빠♥")){
                System.out.printf("이름 : %s   입문 날짜: %s %n", "박한결", entry.getValue());
            }
            else {
                System.out.printf("이름 : %s   입문 날짜: %s %n", entry.getKey(), entry.getValue());
            }
        }

        System.out.println();
        System.out.println("890(팔구공) 불린 횟수 : " + groupNumber);
        System.out.println("여성 채팅 : " + girlsTalkNum + "   남성 채팅 :" + boysTalkNum);
        String lchat = longestChat.replace("회원님","이주연");
        System.out.println("가장 긴 채팅 : " + lchat);

        System.out.println();
        sortedNum = sortByComparator(wordFrequency);
        System.out.println("많이 불린 단어:");
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            System.out.printf("단어 : %s   불린 횟수: %s %n", entry.getKey(), entry.getValue());
        }

        System.out.println();

        sortedNum = sortByComparator(emojiFrequency);
        totalNum = 0;
        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()) {
            totalNum += entry.getValue();
        }
        System.out.println("개인별 이모티콘 횟수 : 총 " + totalNum + "개");

        for(Map.Entry<String, Integer> entry : sortedNum.entrySet()){
            if(entry.getKey().equals("회원님")){
                System.out.printf("이름 : %s   올린 횟수: %s %n", "이주연", entry.getValue());
            }
            else if(entry.getKey().equals("내오빠♥")){
                System.out.printf("이름 : %s   올린 횟수: %s %n", "박한결", entry.getValue());
            }
            else {
                System.out.printf("이름 : %s   올린 횟수: %s %n", entry.getKey(), entry.getValue());
            }
        }



    }

    private static Map<String, Integer> sortByComparator(Map<String, Integer> unsortMap) {

        // Convert Map to List
        List<Map.Entry<String, Integer>> list =
                new LinkedList<Map.Entry<String, Integer>>(unsortMap.entrySet());

        // Sort list with comparator, to compare the Map values
        Collections.sort(list, new Comparator<Map.Entry<String, Integer>>() {
            public int compare(Map.Entry<String, Integer> o1,
                               Map.Entry<String, Integer> o2) {
                return (o2.getValue()).compareTo(o1.getValue());
            }
        });

        // Convert sorted map back to a Map
        Map<String, Integer> sortedMap = new LinkedHashMap<String, Integer>();
        for (Iterator<Map.Entry<String, Integer>> it = list.iterator(); it.hasNext();) {
            Map.Entry<String, Integer> entry = it.next();
            sortedMap.put(entry.getKey(), entry.getValue());
        }
        return sortedMap;
    }
}
