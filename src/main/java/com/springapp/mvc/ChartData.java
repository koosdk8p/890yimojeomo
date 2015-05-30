package com.springapp.mvc;

/**
 * Created by duonki on 5/28/15.
 */
public class ChartData {
    public String getMenu() throws Exception {
        String returnStr = "[[{ key: 'Menu', values: [{ key: '890?', values: 'value' },{ key: '갤러리', values:[{ key: '갤러리'}]} ]}]]";
        System.out.println(returnStr);
        return returnStr;
    }
}
