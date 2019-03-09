package org.apache.dubbo.samples.client;

import com.alibaba.dubbo.config.ApplicationConfig;
import com.alibaba.dubbo.config.ReferenceConfig;
import com.alibaba.dubbo.config.RegistryConfig;
import com.alibaba.dubbo.rpc.service.GenericService;
import org.apache.dubbo.samples.api.GreetingService;


public class Application {
    public static void main(String[] args) {
        // greeting service
//        ReferenceConfig<GreetingService> reference = new ReferenceConfig<>();
//        reference.setApplication(new ApplicationConfig("first-dubbo-client"));
//        reference.setRegistry(new RegistryConfig("zookeeper://127.0.0.1:2181"));
//        reference.setInterface(GreetingService.class);
//        GreetingService genericService = reference.get();
//        System.out.println(genericService.sayHi("aaa"));

        // generic service
        ReferenceConfig<GenericService> reference = new ReferenceConfig<>();
        reference.setApplication(new ApplicationConfig("first-dubbo-client"));
        reference.setRegistry(new RegistryConfig("zookeeper://127.0.0.1:2181"));
        reference.setGeneric(true);
        reference.setInterface(GreetingService.class);
        GenericService genericService = reference.get();
        Object message = genericService.$invoke("sayHi", new String[]{"java.lang.String"}, new Object[]{"aaa"});
        System.out.println(message);
    }
}
