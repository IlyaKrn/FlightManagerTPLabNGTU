package com.ilyakrn.gateway;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.gateway.route.RouteLocator;
import org.springframework.cloud.gateway.route.builder.RouteLocatorBuilder;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class GatewayApplication {

    public static void main(String[] args) {
        SpringApplication.run(GatewayApplication.class, args);
    }

    @Bean
    public RouteLocator myRoutes(RouteLocatorBuilder builder) {
        return builder.routes()
                .route(p -> p
                        .path("/api/airport/get")
                        .filters(f -> f.addRequestHeader("Service-Token", "123"))
                        .uri("http://database-service:8081/"))
                .route(p -> p
                        .path("/api/airport/create")
                        .filters(f -> f.addRequestHeader("Service-Token", "123"))
                        .uri("http://database-service:8081/"))
                .build();
    }
}
