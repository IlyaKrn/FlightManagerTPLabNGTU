package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.AirportModel;
import com.flightmanager.databaseservice.repos.AirportRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
public class AirportController {

    @Autowired
    private AirportRepo repo;

    @GetMapping("${mapping.airport.get}/{id}")
    public ResponseEntity<AirportModel> get(@PathVariable("id") long id) {
        try{
            AirportModel model = repo.findById(id).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.airport.create}")
    public ResponseEntity<AirportModel> get(@RequestBody() AirportModel data) {
        try{
            data.setId(0L);
            AirportModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.airport.update}")
    public ResponseEntity<AirportModel> update(@RequestBody() AirportModel data) {
        try{
            if(repo.findById(data.getId()).orElse(null) == null)
                return ResponseEntity.status(400).build();
            AirportModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.airport.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try{
            repo.deleteById(id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

}
