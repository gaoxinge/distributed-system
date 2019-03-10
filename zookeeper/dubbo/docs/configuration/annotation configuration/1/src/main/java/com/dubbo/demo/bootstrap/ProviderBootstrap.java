package com.dubbo.demo.bootstrap;


import com.dubbo.demo.DemoService;
import com.dubbo.demo.config.ProviderConfiguration;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class ProviderBootstrap {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext();
        context.register(ProviderConfiguration.class);
        context.refresh();
        DemoService demoService = context.getBean(DemoService.class);
        String message = demoService.sayHello("World");
        System.out.println(message);
    }
}
