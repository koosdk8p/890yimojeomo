package com.springapp.mvc;

/**
 * Created by duonki on 5/26/15.
 */
public class Count {
    private String name;
    private String datetime;
    private long measure;


    public String getName() {
        return name;
    }

    public void setName(String metricName) {
        this.name = metricName;
    }

    public String getDatetime() {
        return datetime;
    }

    public void setDatetime(String datetime) {
        this.datetime = datetime;
    }

    public long getMeasure() {
        return measure;
    }

    public void setMeasure(long value) {
        this.measure = value;
    }

    public String toString(){
        return "Name : " + name + ", Date : " + datetime + ", Measure : " + measure;
    }

}
