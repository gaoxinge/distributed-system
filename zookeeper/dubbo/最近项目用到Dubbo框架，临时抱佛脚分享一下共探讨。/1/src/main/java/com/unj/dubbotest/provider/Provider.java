package com.unj.dubbotest.provider;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Provider {
    public static void main(String[] args) throws Exception {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("provider/applicationContext.xml");
        context.start();
        System.in.read();
    }
}
