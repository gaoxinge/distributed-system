package com.dubbo.demo.provider;

import com.alibaba.dubbo.config.annotation.Service;
import com.dubbo.demo.DemoService;

@Service
public class AnnotationDemoService implements DemoService {

    @Override
    public String sayHello(String name) {
        return "Hello, " + name;
    }
}
