package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.PlaneModel;
import com.flightmanager.databaseservice.repos.PlaneRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
public class PlaneController {

    @Autowired
    private PlaneRepo repo;

    @GetMapping("${mapping.plane.get}/{id}")
    public ResponseEntity<PlaneModel> get(@PathVariable("id") long id) {
        try{
            PlaneModel model = repo.findById(id).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.plane.create}")
    public ResponseEntity<PlaneModel> get(@RequestBody() PlaneModel data) {
        try{
            data.setId(0L);
            PlaneModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.plane.update}")
    public ResponseEntity<PlaneModel> update(@RequestBody() PlaneModel data) {
        try{
            if(repo.findById(data.getId()).orElse(null) == null)
                return ResponseEntity.status(400).build();
            PlaneModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.plane.delete}/{id}")
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
