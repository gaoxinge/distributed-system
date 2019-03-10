package com.dubbo.demo.bootstrap;

import com.dubbo.demo.beans.AnnotationDemoServiceConsumer;
import com.dubbo.demo.config.ConsumerConfiguration;
import com.dubbo.demo.config.ProviderConfiguration;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class ConsumerBootstrap {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext providerContext = new AnnotationConfigApplicationContext();
        providerContext.register(ProviderConfiguration.class);
        providerContext.refresh();

        AnnotationConfigApplicationContext consumerContext = new AnnotationConfigApplicationContext();
        consumerContext.register(ConsumerConfiguration.class);
        consumerContext.refresh();

        AnnotationDemoServiceConsumer consumer = consumerContext.getBean(AnnotationDemoServiceConsumer.class);
        System.out.println(consumer.doSayHello("World"));
    }
}
