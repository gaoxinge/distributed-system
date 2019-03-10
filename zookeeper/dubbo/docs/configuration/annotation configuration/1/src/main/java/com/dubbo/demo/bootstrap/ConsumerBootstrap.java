package com.dubbo.demo.bootstrap;

import com.dubbo.demo.config.ConsumerConfiguration;
import com.dubbo.demo.config.ProviderConfiguration;
import com.dubbo.demo.consumer.AnnotationDemoServiceConsumer;
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
