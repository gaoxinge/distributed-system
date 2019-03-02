package com.alibaba.dubbo.demo.pp;

import com.unj.dubbotest.provider.DemoService;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import java.util.List;

public class Consumer {
    public static void main(String[] args) throws Exception {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("consumer/applicationContext.xml");
        context.start();

        DemoService demoService = (DemoService) context.getBean("demoService");
        String hello = demoService.sayHello("tom");
        System.out.println(hello);

        List list = demoService.getUsers();
        for (int i = 0; i < list.size(); i++) {
            System.out.println(list.get(i));
        }

        System.in.read();
    }
}
