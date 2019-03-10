package com.dubbo.demo.consumer;

import com.alibaba.dubbo.config.annotation.Reference;
import com.dubbo.demo.DemoService;

public class AnnotationDemoServiceConsumer {

    @Reference
    private DemoService demoService;

    public String doSayHello(String name) {
        return demoService.sayHello(name);
    }
}
